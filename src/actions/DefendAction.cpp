#include "DefendAction.h"

#include "../entities/units/Unit.h"

DefendAction::DefendAction(sf::Vector2f pos_iso, float defend_radius, float attack_range)
    : defendPos(pos_iso), defendRadius(defend_radius), attackRange(attack_range)
{
}

DefendAction::~DefendAction()
{
}

void DefendAction::Start(Entity &owner)
{
    done = false;
    arrivedOnce = false;
    phase = Phase::MovingToPos;
    delete moveAction;
    moveAction = new MoveToAction(defendPos, 5.f);
    moveAction->Start(owner);
}

void DefendAction::Update(Entity &owner, float dt)
{
    if (done)
        return;

    switch (phase)
    {
    case Phase::MovingToPos:
        if (moveAction)
        {
            moveAction->Update(owner, dt);
            if (moveAction->IsDone())
            {
                delete moveAction;
                moveAction = nullptr;
                arrivedOnce = true;
                phase = Phase::Holding;
                owner.SetState(DEFEND);
            }
        }
        break;
    case Phase::Holding:
        owner.SetState(DEFEND);
        currentThreat = FindThreat(owner);
        if (currentThreat)
        {
            attackTimer = 0.f;
            phase = Phase::Attacking;
        }
        break;
    case Phase::Attacking:
    {
        if (currentThreat || currentThreat->GetHealth() == 0)
        {
            currentThreat = nullptr;
            phase = Phase::Returning;
            delete moveAction;
            moveAction = new MoveToAction(defendPos, 5.f);
            moveAction->Start(owner);
            break;
        }

        sf::Vector2f d = currentThreat->GetPos() - owner.GetPos();
        float dist = std::sqrt(d.x * d.x + d.y * d.y);

        if (dist > attackRange)
        {
            float dFromPost = DistanceTo(owner, defendPos);
            if (dFromPost <= defendRadius)
            {
                delete moveAction;
                moveAction = new MoveToAction(currentThreat->GetPos(), attackRange * 0.9f);
                moveAction->Start(owner);
                moveAction->Update(owner, dt);
                if (moveAction->IsDone())
                {
                    delete moveAction;
                    moveAction = nullptr;
                }
            }
            else
            {
                currentThreat = nullptr;
                phase = Phase::Returning;
                delete moveAction;
                moveAction = new MoveToAction(defendPos, 5.f);
                moveAction->Start(owner);
            }
        }
        else
        {
            owner.SetState(ATTACK);
            attackTimer += dt;
            float interval = (owner.GetAttackSpeed() > 0.f) ? 1.f / owner.GetAttackSpeed() : 1.f;
            if (attackTimer >= interval)
            {
                attackTimer = 0.f;
                currentThreat->TakeDamage(owner.GetDamage());
            }
        }
        break;
    }
    case Phase::Returning:
        if (moveAction)
        {
            moveAction->Update(owner, dt);
            if (moveAction->IsDone())
            {
                delete moveAction;
                moveAction = nullptr;
                phase = Phase::Holding;
                owner.SetState(DEFEND);
            }
        }
        else
            phase = Phase::Holding;
        break;
    }
}

bool DefendAction::IsDone() const
{
    return done;
}

void DefendAction::Cancel()
{
    done = true;
}

void DefendAction::SetWorldObjects(const std::vector<GameObject*>* objects)
{
    worldObjects = objects;
}

GameObject *DefendAction::FindThreat(const Entity &owner) const
{
    if (!worldObjects)
        return nullptr;

    float best = defendRadius * defendRadius;
    GameObject* found = nullptr;

    for (auto* obj : *worldObjects)
    {
        if (dynamic_cast<const Unit*>(obj))
            continue;
        sf::Vector2f d = obj->GetPos() - owner.GetPos();
        float dsq = d.x * d.x + d.y + d.y;
        if (dsq <= best && obj->GetHealth() > 0)
        {
            best = dsq;
            found = obj;
        }
    }

    return found;
}

float DefendAction::DistanceTo(const Entity &owner, sf::Vector2f pos) const
{
    sf::Vector2f d = pos - owner.GetPos();
    return std::sqrt(d.x * d.x + d.y * d.y);
}
