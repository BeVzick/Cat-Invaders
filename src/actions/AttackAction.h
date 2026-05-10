#pragma once

#include "IAction.h"
#include "../GameObject.h"

class AttackAction : public IAction
{
public:
    AttackAction(GameObject& target);
    ~AttackAction();

private:
    GameObject& target;
};
