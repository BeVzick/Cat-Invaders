#pragma once

#include "IAction.h"
#include <SFML/System/Vector2.hpp>

class MoveToAction : public IAction
{
public:
    MoveToAction(sf::Vector2f target_pos);
    ~MoveToAction();

    void Update(Entity& owner, float dt) override;
    bool IsDone() const override;

private:
    sf::Vector2f targetPos;
    bool isDone = false;
};
