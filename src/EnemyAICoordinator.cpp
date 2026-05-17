#include "EnemyAICoordinator.h"

#include "entities/enemies/Enemy.h"
#include "EnemyAI.h"
#include "buildings/EnemyCamp.h"
#include <algorithm>

EnemyAICoordinator::EnemyAICoordinator(EnemyCamp &camp)
    : camp(camp)
{
}

EnemyAICoordinator::~EnemyAICoordinator()
{
    for (auto& e : entries)
        delete e.ai;
}

void EnemyAICoordinator::Update(float dt, const std::vector<GameObject*>& world_objects, sf::Vector2f player_base_pos)
{
    for (auto it = entries.begin(); it != entries.end();)
    {
        if (it->enemy->GetHealth() == 0)
        {
            delete it->ai;
            it = entries.erase(it);
        }
        else
            ++it;
    }
 
    unsigned aliveCount = static_cast<unsigned>(entries.size());
 
    if (!rallyIssued && aliveCount >= rallyThreshold)
    {
        rallyIssued = true;
        sf::Vector2f rp = ComputeRallyPoint();
        for (auto& e : entries)
            e.ai->NotifyRallyPoint(rp);
    }
 
    assaultTimer += dt;
    if (assaultTimer >= assaultInterval && aliveCount > 0)
    {
        assaultTimer = 0.f;
        rallyIssued  = false;
 
        for (auto& e : entries)
            e.ai->OrderAssault(player_base_pos);
    }
 
    for (auto& e : entries)
        e.ai->Update(dt, world_objects, player_base_pos);

}

void EnemyAICoordinator::RegisterEnemy(Enemy *enemy)
{
    EnemyAI* ai = new EnemyAI(*enemy, camp);
    entries.push_back({ enemy, ai });
    rallyIssued = false;
}

void EnemyAICoordinator::UnregisterEnemy(Enemy *enemy)
{
    auto it = std::find_if(entries.begin(), entries.end(),
        [enemy](const EnemyEntry& e) { return e.enemy == enemy; }
    );

    if (it != entries.end())
    {
        delete it->ai;
        entries.erase(it);
    }
}

void EnemyAICoordinator::SetRallyThreshold(unsigned n)
{
    rallyThreshold = n;
}

void EnemyAICoordinator::SetAssaultInterval(float seconds)
{
    assaultInterval = seconds;
}

sf::Vector2f EnemyAICoordinator::ComputeRallyPoint() const
{
    sf::Vector2f campPos = camp.GetPos();
    return { campPos.x + 60.f, campPos.y };

}
