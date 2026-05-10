#include "Unit.h"

#include <imgui.h>
#include <imgui-SFML.h>

Unit::Unit(sf::Texture& texture, sf::Vector2i frame_size, bool has_group)
    : Entity(texture, frame_size), hasGroup(has_group)
{
}

Unit::~Unit()
{
}

void Unit::ShowData()
{
    Entity::ShowData();

    ImGui::Separator();
    ImGui::LabelText("Training Time", "%ds", trainingTime);
}

void Unit::UpdateAnimations(float dt)
{
    if (animationComponent)
    {
        std::string animation;
        switch (state)
        {
        case IDLE: animation = "idle1";
            break;
        case MOVE_DOWN: animation = "walk_down";
            break;
        case MOVE_DOWN_LEFT: animation = "walk_down_left";
            break;
        case MOVE_LEFT: animation = "walk_left";
            break;
        case MOVE_UP_LEFT: animation = "walk_up_left";
            break;
        case MOVE_UP: animation = "walk_up";
            break;
        case MOVE_UP_RIGHT: animation = "walk_up_right";
            break;
        case MOVE_RIGHT: animation = "walk_right";
            break;
        case MOVE_DOWN_RIGHT: animation = "walk_down_right";
            break;
        default: animation = "default";
            break;
        }

        if (isSelected)
            animation.append("-selected");

        animationComponent->Play(animation, dt);
    }
}

bool Unit::GetHasGroup()
{
    return hasGroup;
}

void Unit::SetHasGroup(bool has_group)
{
    hasGroup = has_group;
}
