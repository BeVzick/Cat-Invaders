#include "EnemyCamp.h"

#include "../entities/units/Unit.h"
#include "../entities/enemies/Bat.h"
#include <algorithm>
#include <SFML/Graphics/RenderTarget.hpp>
#include <imgui.h>

AggroEllipse::AggroEllipse(float radius_x, float radius_y, unsigned point_count)
    : fill(sf::PrimitiveType::TriangleFan, point_count + 2), outline(sf::PrimitiveType::LineStrip, point_count + 1),
    rx(radius_x), ry(radius_y), pointCount(point_count)
{
}

void AggroEllipse::SetPosition(sf::Vector2f pos)
{
    center = pos;
    Rebuild();
}

void AggroEllipse::Render(sf::RenderTarget& target)
{
    target.draw(fill);
    target.draw(outline);
}

void AggroEllipse::Rebuild()
{
    const sf::Color fillCol = { 255, 50, 50, 18 };
    const sf::Color outlineCol = { 255, 80, 80, 110 };

    fill[0].position = center;
    fill[0].color = fillCol;

    for (unsigned i = 0; i <= pointCount; ++i)
    {
        float angle = static_cast<float>(i) / static_cast<float>(pointCount) * 2.f * M_PI;
        sf::Vector2f p = { center.x + rx * std::cos(angle), center.y + ry * std::sin(angle) };
        fill[i + 1].position = p;
        fill[i + 1].color = fillCol;
        outline[i].position = p;
        outline[i].color = outlineCol;
    }
}

EnemyCamp::EnemyCamp(sf::Texture &texture, std::vector<GameObject *>& worldObjects, std::map<std::string, sf::Texture *>& textures)
    : EnemyCamp(texture, {250, 250}, 30.f, 180.f, 4, worldObjects, textures)
{
}

EnemyCamp::EnemyCamp(sf::Texture &texture, sf::Vector2f pos, float spawn_interval, float aggro_radius, unsigned max_enemies,
    std::vector<GameObject *>& worldObjects, std::map<std::string, sf::Texture *>& textures)
    : GameObject(texture), worldObjects(worldObjects), textures(textures), spawnInterval(spawn_interval), aggroRadius(aggro_radius), maxEnemies(max_enemies),
      aggroShape(aggro_radius, aggro_radius * 0.5f, 64)
{
    SetPos(pos);
    aggroShape.SetPosition(pos);
    maxHealth = 300;
    health = maxHealth;
}

EnemyCamp::~EnemyCamp()
{
    for (auto* e : spawnedEnemies)
        delete e;
}

void EnemyCamp::Update(sf::Vector2f mouse_pos_view, float dt)
{
    GameObject::Update(mouse_pos_view, dt);

    if (destroyed)
        return;

    spawnedEnemies.erase(
        std::remove_if(spawnedEnemies.begin(), spawnedEnemies.end(),
            [](Enemy* e) { return e->GetHealth() <= 0; }
        ),
        spawnedEnemies.end()
    );

    for (auto* e : spawnedEnemies)
    {
        e->Update({}, dt);
        e->UpdateAnimations(dt);
    }

    spawnTimer += dt;
    if (spawnTimer >= spawnInterval && spawnedEnemies.size() < maxEnemies)
    {
        spawnTimer = 0.f;

        for (auto& entry : waveEntries)
        {
            if (spawnedEnemies.size() >= maxEnemies)
                break;

            for (unsigned i = 0; i < entry.count; ++i)
            {
                if (spawnedEnemies.size() >= maxEnemies)
                    break;
            }
        }

        SpawnWave();
    }
}

void EnemyCamp::Render(sf::RenderTarget& target)
{
    if (!destroyed)
        aggroShape.Render(target);

    GameObject::Render(target);

    for (auto* e : spawnedEnemies)
        e->Render(target);
}

void EnemyCamp::ShowData()
{
    ImGui::LabelText("Health", "%u / %u", health, maxHealth);
    ImGui::LabelText("Enemies", "%zu / %u", spawnedEnemies.size(), maxEnemies);
    ImGui::LabelText("Aggroed", "%s", aggroed ? "Yes" : "No");
    ImGui::LabelText("Aggro Radius", "%.0f x %.0f", aggroRadius, aggroRadius * 0.5f);
}

void EnemyCamp::AddWaveEntry(EnemyType type, unsigned count)
{
    waveEntries.push_back({type, count});
}

void EnemyCamp::TakeDamage(unsigned damage)
{
    if (health <= damage)
    {
        health = 0;
        destroyed = true;
    }
    else
        health -= damage;
}

bool EnemyCamp::IsDestriyed() const
{
    return destroyed;
}

void EnemyCamp::CheckAggro(const std::vector<GameObject *> &objects, const std::vector<GameObject *> &worldObjects)
{
    if (aggroed || destroyed)
        return;

    sf::Vector2f campPos = GetPos();
    float rx = aggroRadius;
    float ry = aggroRadius * 0.5f;

    for (auto* obj : objects)
    {
        if (!dynamic_cast<Unit*>(obj))
            continue;
        
        sf::Vector2f d = obj->GetPos() - campPos;

        float elipsedCheck = ((d.x * d.x) / (rx * rx) + (d.y * d.y) / (ry * ry));
        if (elipsedCheck <= 1.f)
        {
            aggroed = true;
            // for (auto* e : spawnedEnemies)
                // e->InitAI(worldObjects, campPos);
            break;
        }
    }
}

float EnemyCamp::GetAggroRadius() const
{
    return aggroRadius;
}

const std::vector<Enemy *> &EnemyCamp::GetSpawnedEnemies()
{
    return spawnedEnemies;
}

nlohmann::json EnemyCamp::Serialize()
{
    nlohmann::json enemyCamp = GameObject::Serialize();

    enemyCamp["spawn_timer"] = spawnTimer;
    enemyCamp["aggroed"] = aggroed;
    enemyCamp["destroyed"] = destroyed;
    enemyCamp["spawned_enemies"] = nlohmann::json::array();
    for (auto* e : spawnedEnemies)
        enemyCamp["spawned_enemies"].push_back(e->Serialize());

    return enemyCamp;
}

void EnemyCamp::Deserialize(const nlohmann::json& data)
{
    GameObject::Deserialize(data);

    spawnTimer = data.value("spawn_timer", 0);
    aggroed = data.value("aggroed", false);
    destroyed = data.value("destroyed", false);
    
    for (auto* e : spawnedEnemies)
        delete e;
    spawnedEnemies.clear();
    for (nlohmann::json eJson : data["spawned_enemies"])
    {
        Enemy* e;
        std::string type = eJson.value("type", "");

        if (type == "Bat")
            e = new Bat(*textures["bat"]);

        e->Deserialize(eJson);

        spawnedEnemies.push_back(e);
    }
}

std::string EnemyCamp::GetType() const
{
    return "EnemyCamp";
}


void EnemyCamp::SpawnWave()
{
    if (destroyed || spawnedEnemies.size() >= maxEnemies)
        return;

    sf::Vector2f campPos = GetPos();

    for (const auto& entry : waveEntries)
    {
        for (unsigned i = 0; i < entry.count; ++i)
        {
            if (spawnedEnemies.size() >= maxEnemies)
                return;

            Enemy* newEnemy = nullptr;

            switch (entry.type)
            {
            case EnemyType::Bat:
                newEnemy = new Bat(*textures["bat"]);
                break;
            }

            if (newEnemy)
            {
                float offsetX = (rand() % 100 - 50) * 0.5f; 
                float offsetY = (rand() % 100 - 50) * 0.5f;
                newEnemy->SetPos({campPos.x + offsetX, campPos.y + offsetY});

                if (aggroed)
                {
                    // newEnemy->InitAI(worldObjects, campPos); // Розкоментуй, якщо метод готовий
                }

                spawnedEnemies.push_back(newEnemy);
            }
        }
    }
}
