#pragma once

#include "IAction.h"
#include "../entities/Entity.h"
#include <SFML/System/Vector2.hpp>

class Entity;

class MoveToAction : public IAction
{
public:
    MoveToAction(sf::Vector2f target_pos, float arrival_threshold = 5.f);
    ~MoveToAction();

    void Start(Entity& owner) override;
    void Update(Entity& owner, float dt) override;
    bool IsDone() const override;
    void Cancel() override;

private:
    sf::Vector2f targetPos;
    float arrivalThreshold;
    bool done = false;

    static EntityState DirectionFromAngle(float angle_rad);
};
