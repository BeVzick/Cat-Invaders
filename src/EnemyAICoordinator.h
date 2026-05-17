#pragma once

#include <vector>
#include <SFML/System/Vector2.hpp>

class Enemy;
class EnemyAI;
class EnemyCamp;
class GameObject;

class EnemyAICoordinator
{
public:
    EnemyAICoordinator(EnemyCamp& camp);
    ~EnemyAICoordinator();
    
    void Update(float dt, const std::vector<GameObject*>& world_objects, sf::Vector2f player_base_pos);
    
    void RegisterEnemy(Enemy* enemy);
    void UnregisterEnemy(Enemy* enemy);

    void SetRallyThreshold(unsigned n);
    void SetAssaultInterval(float seconds);


private:
    EnemyCamp& camp;

    struct EnemyEntry
    {
        Enemy* enemy;
        EnemyAI* ai;
    };

    std::vector<EnemyEntry> entries;

    unsigned rallyThreshold = 3;
    float assaultInterval = 60.f;
    float assaultTimer = 0.f;
    bool rallyIssued = false;

    sf::Vector2f ComputeRallyPoint() const;
};
