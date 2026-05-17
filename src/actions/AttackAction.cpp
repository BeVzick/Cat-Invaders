#include "AttackAction.h"

#include "../entities/Entity.h"

AttackAction::AttackAction(GameObject &target, float attack_range, float chase_threshold)
    : target(target), attackRange(attack_range), chaseThreshold(chase_threshold), 
      attackTimer(0.f), done(false), moveAction(nullptr)
{
}

AttackAction::~AttackAction()
{
}

void AttackAction::Start(Entity& owner)
{
    done = false;
    attackTimer = 0.f;
    delete moveAction;
    moveAction = nullptr;
}

void AttackAction::Update(Entity& owner, float dt)
{
    if (done)
        return;

    float dist = DistanceTo(owner);

    if (target.GetHealth() == 0 || (chaseThreshold > 0 && dist > chaseThreshold))
    {
        owner.SetState(DEFAULT);
        done = true;
        return;
    }

    if (!InRange(owner))
    {
        owner.SetState(DEFAULT);
        if (!moveAction)
        {
            moveAction = new MoveToAction(target.GetPos(), attackRange * 0.9f);
            moveAction->Start(owner);
        }

        moveAction->Update(owner, dt);

        if (moveAction->IsDone())
        {
            delete moveAction;
            moveAction = nullptr;
        }
        return;
    }

    if (moveAction)
    {
        delete moveAction;
        moveAction = nullptr;
    }

    owner.SetState(ATTACK);
    attackTimer += dt;
    
    float interval = (owner.GetAttackSpeed() > 0.f) ? 1.f / owner.GetAttackSpeed() : 1.f;

    if (attackTimer >= interval)
    {
        attackTimer -= interval;
        target.TakeDamage(owner.GetDamage());
    }
}

bool AttackAction::IsDone() const
{
    return done;
}

void AttackAction::Cancel()
{
    done = true;
    delete moveAction;
    moveAction = nullptr;
}

bool AttackAction::InRange(const Entity &owner) const
{
    return DistanceTo(owner) <= attackRange;
}

float AttackAction::DistanceTo(const Entity& owner) const
{
    sf::Vector2f d = target.GetPos() - owner.GetPos();
    return std::sqrt(d.x * d.x + d.y * d.y);
}
