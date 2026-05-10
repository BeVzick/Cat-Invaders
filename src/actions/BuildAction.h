#pragma once

#include "IAction.h"

class Building;

class BuildAction : public IAction
{
public:
    BuildAction(Building& building);
    ~BuildAction();

private:
    Building& building;
};
