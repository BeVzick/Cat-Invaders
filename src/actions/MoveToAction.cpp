#include "MoveToAction.h"

#include "../entities/Entity.h"

MoveToAction::MoveToAction(sf::Vector2f target_pos, float arrival_threshold)
    : targetPos(target_pos), arrivalThreshold(arrival_threshold), done(false)
{
}

MoveToAction::~MoveToAction()
{
}

void MoveToAction::Start(Entity &owner)
{
    done = false;
    sf::Vector2f dir = targetPos - owner.GetPos();
    float dist = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    if (dist > arrivalThreshold)
        owner.SetState(DirectionFromAngle(std::atan2(dir.y, dir.x)));
}

void MoveToAction::Update(Entity &owner, float dt)
{
    if (done)
        return;

    sf::Vector2f currPos = owner.GetPos();
    sf::Vector2f dir = targetPos - currPos;
    float dist = std::sqrt(dir.x * dir.x + dir.y * dir.y);

    if (dist <= arrivalThreshold)
    {
        owner.SetState(DEFAULT);
        done = true;
        return;
    }

    dir /= dist;
    float speed = owner.GetSpeed();
    float step = std::min(speed * dt, dist - arrivalThreshold);
    owner.SetPos(currPos + dir * step);
    owner.SetState(DirectionFromAngle(std::atan2(dir.y, dir.x)));
}

bool MoveToAction::IsDone() const
{
    return done;
}

void MoveToAction::Cancel()
{
    done = true;
}

EntityState MoveToAction::DirectionFromAngle(float angle_rad)
{
    if (angle_rad < 0.f)
        angle_rad += 2.f * static_cast<float>(M_PI);

    int octant = static_cast<int>(angle_rad / (2.f * static_cast<float>(M_PI) / 8.f)) % 8;

    switch (octant)
    {
    case 0: return MOVE_RIGHT;
    case 1: return MOVE_DOWN_RIGHT;
    case 2: return MOVE_DOWN;
    case 3: return MOVE_DOWN_LEFT;
    case 4: return MOVE_LEFT;
    case 5: return MOVE_UP_LEFT;
    case 6: return MOVE_UP;
    case 7: return MOVE_UP_RIGHT;
    default: return DEFAULT;
    }
}
