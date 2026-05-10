#include "Entity.h"

#include <imgui.h>

Entity::Entity(sf::Texture& texture, sf::Vector2i frame_size)
    : GameObject(texture, frame_size), state(DEFAULT)
{
}

Entity::~Entity()
{
    while (!actions.empty())
    {
        delete actions.front();
        actions.pop();
    }
}

void Entity::ShowData()
{
    GameObject::ShowData();

    ImGui::LabelText("Damage", "%d", damage);
    ImGui::LabelText("Attack Speed", "%.2f", attackSpeed);
    ImGui::LabelText("Speed", "%.2f", speed);
}

void Entity::Update(sf::Vector2f mouse_pos_view, float dt)
{
    GameObject::Update(mouse_pos_view, dt);

    if (!actions.empty())
    {
        IAction* current = actions.front();
        current->Update(*this, dt);

        if (current->IsDone())
        {
            delete current;
            actions.pop();

            if (!actions.empty())
                actions.front()->Start(*this);
        }
    }
    // else - if doesn't hava an action
}

void Entity::IssueCommand(IAction *action, bool shift_queue)
{
    if (!shift_queue)
    {
        while (!actions.empty())
        {
            IAction* current = actions.front();
            current->Cancel();
            delete current;
            actions.pop();
        }
    }

    actions.push(action);

    if (actions.size() == 1)
        actions.front()->Start(*this);
}

EntityState Entity::GetState()
{
    return state;
}

unsigned Entity::GetDamage()
{
    return damage;
}

float Entity::GetAttackSpeed()
{
    return attackSpeed;
}

float Entity::GetSpeed()
{
    return speed;
}

void Entity::SetState(EntityState state)
{
    this->state = state;
}
