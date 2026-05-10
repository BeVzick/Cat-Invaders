#include "MoveToAction.h"

#include "../entities/Entity.h"

MoveToAction::MoveToAction(sf::Vector2f target_pos)
    : targetPos(target_pos)
{
}

MoveToAction::~MoveToAction()
{
}

void MoveToAction::Update(Entity& owner, float dt)
{
    sf::Vector2f currPos = owner.GetPos();
    sf::Vector2f dir = targetPos - currPos;

    float distance = std::sqrt(dir.x * dir.x + dir.y * dir.y);

    if (distance <= 5.0f)
    {
        isDone = true;
        owner.SetState(DEFAULT);
        return;
    }

    dir /= distance;

    owner.SetPos(currPos + dir * owner.GetSpeed() * dt);

    float angle = std::atan2(dir.y, dir.x);
    int octant = std::round(8 * angle / (2 * M_PI) + 8);
    octant %= 8;

    EntityState state = DEFAULT;
    switch (octant)
    {
    case 0: state = MOVE_RIGHT;
        break;
    case 1: state = MOVE_DOWN_RIGHT;
        break;
    case 2: state = MOVE_DOWN;
        break;
    case 3: state = MOVE_DOWN_LEFT;
        break;
    case 4: state = MOVE_LEFT;
        break;
    case 5: state = MOVE_UP_LEFT;
        break;
    case 6: state = MOVE_UP;
        break;
    case 7: state = MOVE_UP_RIGHT;
        break;
    }
    owner.SetState(state);
}

bool MoveToAction::IsDone() const
{
    return isDone;
}
