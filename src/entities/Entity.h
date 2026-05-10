#pragma once

#include "../GameObject.h"
#include "../actions/IAction.h"
#include <queue>

enum EntityState {
    DEFAULT = 0, IDLE, 
    MOVE_DOWN, MOVE_DOWN_LEFT, MOVE_LEFT, MOVE_UP_LEFT, MOVE_UP, MOVE_UP_RIGHT, MOVE_RIGHT, MOVE_DOWN_RIGHT,
    ATTACK,
    DEFEND
};

class Entity : public GameObject
{
public:
    Entity(sf::Texture& texture, sf::Vector2i frame_size = {32, 32});
    virtual ~Entity();

    virtual void ShowData() override;
    void Update(sf::Vector2f mouse_pos_view, float dt) override;

    void IssueCommand(IAction* action, bool shift_queue = false);

    EntityState GetState();
    unsigned GetDamage();
    float GetAttackSpeed();
    float GetSpeed();
    void SetState(EntityState state);

protected:
    std::queue<IAction*> actions;
    EntityState state;
    unsigned damage;
    float attackSpeed;
    float speed;
};
