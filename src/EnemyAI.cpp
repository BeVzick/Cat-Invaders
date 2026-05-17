#include "EnemyAI.h"

#include "buildings/EnemyCamp.h"
#include "entities/units/Unit.h"

EnemyAI::EnemyAI(Enemy &owner, EnemyCamp &camp)
    : owner(owner), camp(camp)
{
    wanderTarget = camp.GetPos();
}

void EnemyAI::Update(float dt, const std::vector<GameObject *> &world_objects, sf::Vector2f base_target_pos)
{
    switch (state)
    {
    case EnemyAIState::Wander: UpdateWander(dt, world_objects);
        break;
    case EnemyAIState::Chase: UpdateChase(dt);
        break;
    case EnemyAIState::Attack: UpdateAttack(dt, world_objects);
        break;
    case EnemyAIState::Rally: UpdateRally(dt);
        break;
    case EnemyAIState::Assault: UpdateAssault(dt);
        break;
    }

    if (state == EnemyAIState::Wander || state == EnemyAIState::Chase)
    {
        GameObject* nearest = FindNearestUnit(world_objects);
        if (nearest && DistanceTo(nearest->GetPos()) <= sightRadius)
        {
            target = nearest;
            TransitionTo(EnemyAIState::Chase);
        }
    }
}

EnemyAIState EnemyAI::GetState() const
{
    return state;
}

void EnemyAI::NotifyRallyPoint(sf::Vector2f point)
{
    if (state != EnemyAIState::Assault)
    {
        rallyPoint = point;
        rallyWaitTimer = 0.f;
        TransitionTo(EnemyAIState::Rally);
    }
}

void EnemyAI::OrderAssault(sf::Vector2f target)
{
    assaultTarget = target;
    TransitionTo(EnemyAIState::Assault);
}

void EnemyAI::TransitionTo(EnemyAIState new_state)
{
    state = new_state;
    path.clear();
    pathIndex = 0;
    pathTimer = 0.f;

    if (new_state == EnemyAIState::Wander)
    {
        wanderTimer = 0.f;
        wanderTarget = RandomPointNear(camp.GetPos(), wanderRadius);
    }
    else if (new_state == EnemyAIState::Rally)
        RequestPath(rallyPoint);
    else if (new_state == EnemyAIState::Assault)
        RequestPath(assaultTarget);
}

void EnemyAI::UpdateWander(float dt, const std::vector<GameObject *> &world_objects)
{
    wanderTimer += dt;

    bool reached = MoveAlongPath(dt);

    if (reached || wanderTimer >= wanderInterval)
    {
        wanderTimer = 0.f;
        wanderTarget = RandomPointNear(camp.GetPos(), wanderRadius);
        RequestPath(wanderTarget);
    }
}

void EnemyAI::UpdateChase(float dt)
{
    if (!TargetStillValid())
    {
        target = nullptr;
        TransitionTo(EnemyAIState::Wander);
        return;
    }

    if (DistanceToCamp() > leashRadius)
    {
        target = nullptr;
        TransitionTo(EnemyAIState::Wander);
        return;
    }

    float distToTarget = DistanceTo(target->GetPos());

    if (distToTarget <= attackRange)
    {
        TransitionTo(EnemyAIState::Attack);
        return;
    }

    pathTimer += dt;
    if (pathTimer >= pathRefreshInterval || path.empty())
    {
        pathTimer = 0.f;
        RequestPath(target->GetPos());
    }

    MoveAlongPath(dt);
}

void EnemyAI::UpdateAttack(float dt, const std::vector<GameObject *> &world_objects)
{
        if (!TargetStillValid())
    {
        target = nullptr;
        target = FindNearestUnit(world_objects);
        if (target && DistanceTo(target->GetPos()) <= sightRadius)
            TransitionTo(EnemyAIState::Chase);
        else
            TransitionTo(EnemyAIState::Wander);
        return;
    }
 
    float distToTarget = DistanceTo(target->GetPos());
 
    if (distToTarget > attackRange)
    {
        TransitionTo(EnemyAIState::Chase);
        return;
    }
 
    owner.SetState(ATTACK);
 
    attackTimer += dt;
    float interval = (owner.GetAttackSpeed() > 0.f) ? 1.f / owner.GetAttackSpeed() : 1.f;
    if (attackTimer >= interval)
    {
        attackTimer -= interval;
        target->TakeDamage(owner.GetDamage());
    }
}

void EnemyAI::UpdateRally(float dt)
{
        bool arrived = MoveAlongPath(dt);
 
    if (arrived)
    {
        rallyWaitTimer += dt;
        owner.SetState(IDLE);
 
        if (rallyWaitTimer >= rallyTimeout)
            TransitionTo(EnemyAIState::Wander);
    }

}

void EnemyAI::UpdateAssault(float dt)
{
    bool arrived = MoveAlongPath(dt);
    if (arrived)
        TransitionTo(EnemyAIState::Wander);
}

GameObject *EnemyAI::FindNearestUnit(const std::vector<GameObject *> &world_objects) const
{
    GameObject* nearest  = nullptr;
    float bestDist = std::numeric_limits<float>::max();
 
    for (auto* obj : world_objects)
    {
        if (!dynamic_cast<Unit*>(obj))
            continue;
        if (obj->GetHealth() == 0)
            continue;
 
        sf::Vector2f d = obj->GetPos() - owner.GetPos();
        float dist = std::sqrt(d.x * d.x + d.y * d.y);
        if (dist < bestDist)
        {
            bestDist = dist;
            nearest  = obj;
        }
    }
    return nearest;
}

bool EnemyAI::TargetStillValid() const
{
    return target != nullptr && target->GetHealth() > 0;
}

float EnemyAI::DistanceTo(sf::Vector2f pos) const
{
    sf::Vector2f d = pos - owner.GetPos();
    return std::sqrt(d.x * d.x + d.y * d.y);
}

float EnemyAI::DistanceToCamp() const
{
    return DistanceTo(camp.GetPos());
}

sf::Vector2f EnemyAI::RandomPointNear(sf::Vector2f center, float radius) const
{
    float angle = static_cast<float>(std::rand()) / RAND_MAX * 2.f * M_PI;
    float r = static_cast<float>(std::rand()) / RAND_MAX * radius;
    return { center.x + std::cos(angle) * r, center.y + std::sin(angle) * r };
}

bool EnemyAI::MoveAlongPath(float dt)
{
    if (path.empty() || pathIndex >= path.size())
        return true;
 
    sf::Vector2f target_pos = path[pathIndex];
    MoveDirectlyTo(target_pos, dt);
 
    if (DistanceTo(target_pos) < 4.f)
    {
        ++pathIndex;
        if (pathIndex >= path.size())
            return true;
    }
    return false;
}

void EnemyAI::RequestPath(sf::Vector2f goal)
{
    auto isWalkable = [](sf::Vector2i) { return true; };
 
    path = Pathfinder::FindPath(owner.GetPos(), goal, {32.f, 16.f}, isWalkable);
    pathIndex = 0;
}

void EnemyAI::MoveDirectlyTo(sf::Vector2f goal, float dt)
{
    sf::Vector2f d = goal - owner.GetPos();
    float dist = std::sqrt(d.x * d.x + d.y * d.y);
    if (dist < 0.1f)
        return;
 
    sf::Vector2f dir  = d / dist;
    float step = std::min(owner.GetSpeed() * dt, dist);
    owner.SetPos(owner.GetPos() + dir * step);
 
    float angle = std::atan2(dir.y, dir.x);
    if (angle < 0.f)
        angle += 2.f * 3.14159f;
    int octant = static_cast<int>(angle / (2.f * M_PI / 8.f)) % 8;
    static const EntityState dirs[8] = {
        MOVE_RIGHT, MOVE_DOWN_RIGHT, MOVE_DOWN, MOVE_DOWN_LEFT,
        MOVE_LEFT,  MOVE_UP_LEFT,   MOVE_UP,   MOVE_UP_RIGHT
    };
    owner.SetState(dirs[octant]);
}
