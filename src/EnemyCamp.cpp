#include "EnemyCamp.h"

#include "entities/units/Unit.h"
#include <algorithm>
#include <SFML/Graphics/RenderTarget.hpp>
#include <imgui.h>

EnemyCamp::EnemyCamp(sf::Texture &texture, sf::Vector2f pos, float spawn_interval, float aggro_radius, unsigned max_enemies)
    : GameObject(texture), spawnInterval(spawn_interval), aggroRadius(aggro_radius), maxEnemies(max_enemies)
{
    SetPos(pos);
    maxHealth = 300;
    health = maxHealth;

    aggroCircle.setRadius(aggroRadius);
    aggroCircle.setOrigin({aggroRadius, aggroRadius});
    aggroCircle.setFillColor(sf::Color(255, 50, 50, 20));
    aggroCircle.setOutlineColor(sf::Color(255, 50, 50, 100));
    aggroCircle.setOutlineThickness(1.f);
    aggroCircle.setPosition(pos);
}

EnemyCamp::~EnemyCamp()
{
    for (auto* e : spawnedEnemies)
        delete e;
}

void EnemyCamp::Update(sf::Vector2f mouse_pos_view, float dt)
{
    if (destroyed)
        return;

    spawnedEnemies.erase(
        std::remove_if(spawnedEnemies.begin(), spawnedEnemies.end(),
            [](Enemy* e) { return e->GetHealth() <= 0; }
        ),
        spawnedEnemies.end()
    );

    for (auto* e : spawnedEnemies)
        e->Update({}, dt);

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
    }
}

void EnemyCamp::Render(sf::RenderTarget& target)
{
    if (!destroyed)
        target.draw(aggroCircle);

    GameObject::Render(target);

    for (auto* e : spawnedEnemies)
        e->Render(target);
}

void EnemyCamp::ShowData()
{
    ImGui::LabelText("Health", "%u / %u", health, maxHealth);
    ImGui::LabelText("Enemies", "%zu / %u", spawnedEnemies.size(), maxEnemies);
    ImGui::LabelText("Aggroed", "%s", aggroed ? "Yes" : "No");
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
    float radiusSq = aggroRadius * aggroRadius;

    for (auto* obj : objects)
    {
        if (!dynamic_cast<Unit*>(obj))
            continue;
        
        sf::Vector2f d = obj->GetPos() - campPos;
        if (d.x * d.x - d.y * d.y <= radiusSq)
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
