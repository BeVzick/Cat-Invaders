#pragma once

#include "MoveToAction.h"
#include "../GameObject.h"

class AttackAction : public IAction
{
public:
    AttackAction(GameObject& target, float attack_range = 28.f, float chase_threshold = 300.f);
    ~AttackAction();

    void Start(Entity& owner) override;
    void Update(Entity& owner, float dt) override;
    bool IsDone() const override;
    void Cancel() override;

private:
    GameObject& target;
    float attackRange;
    float chaseThreshold;
    float attackTimer;
    bool done;

    MoveToAction* moveAction;

    bool InRange(const Entity& owner) const;
    float DistanceTo(const Entity& owner) const;
};
