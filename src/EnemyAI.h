#pragma once

#include "utills/Pathfinder.h"

class Enemy;
class EnemyCamp;
class GameObject;

class EnemyAI
{
public:
    EnemyAI(Enemy& owner, EnemyCamp& camp);

    void Update(float dt, const std::vector<GameObject*>& world_objects, sf::Vector2f base_target_pos);

    EnemyAIState GetState() const;

    void NotifyRallyPoint(sf::Vector2f point);
    void OrderAssault(sf::Vector2f target);

private:
    Enemy& owner;
    EnemyCamp& camp;

    EnemyAIState state = EnemyAIState::Wander;

    sf::Vector2f wanderTarget;
    float wanderTimer = 0.f;
    static constexpr float wanderInterval = 3.f;
    static constexpr float wanderRadius = 80.f;

    GameObject* target = nullptr;
    float attackTimer = 0.f;
    static constexpr float sightRadius = 150.f;
    static constexpr float attackRange = 30.f;
    static constexpr float leashRadius = 250.f;

    sf::Vector2f rallyPoint;
    sf::Vector2f assaultTarget;
    float rallyWaitTimer = 0.f;
    static constexpr float rallyTimeout = 5.f;

    std::vector<sf::Vector2f> path;
    std::size_t pathIndex = 0;
    float pathTimer = 0.f;
    static constexpr float pathRefreshInterval = 1.5f;

    void TransitionTo(EnemyAIState new_state);
    void UpdateWander(float dt, const std::vector<GameObject*>& world_objects);
    void UpdateChase(float dt);
    void UpdateAttack(float dt, const std::vector<GameObject*>& world_objects);
    void UpdateRally(float dt);
    void UpdateAssault(float dt);

    GameObject* FindNearestUnit(const std::vector<GameObject*>& world_objects) const;
    bool TargetStillValid() const;
    float DistanceTo(sf::Vector2f pos) const;
    float DistanceToCamp() const;
    sf::Vector2f RandomPointNear(sf::Vector2f center, float radius) const;
    bool MoveAlongPath(float dt);
    void RequestPath(sf::Vector2f goal);
    void MoveDirectlyTo(sf::Vector2f goal, float dt);
};
