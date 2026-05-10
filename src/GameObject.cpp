#include "GameObject.h"

#include "utills/CoordinatesConverter.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <string>
#include <imgui.h>

GameObject::GameObject(sf::Texture& texture, sf::Vector2i frame_size, sf::Vector2f pos)
    : sprite(texture), pos(pos), isSelected(false)
{
    animationComponent = new AnimationComponent(sprite, frame_size);
}

GameObject::~GameObject()
{
    delete animationComponent;
}

void GameObject::ShowData()
{
    ImGui::LabelText("Health", "%d / %d", health, maxHealth);
}

void GameObject::Update(sf::Vector2f mouse_pos_view, float dt)
{
}

void GameObject::Render(sf::RenderTarget& target)
{
    target.draw(sprite);
}

sf::Vector2f GameObject::GetPos()
{
    return pos;
}

unsigned GameObject::GetHealth()
{
    return health;
}

void GameObject::SetPos(sf::Vector2f pos)
{
    this->pos = pos;
    sprite.setPosition(pos);
}

void GameObject::SetIsSelected(bool is_selected)
{
    isSelected = is_selected;
}
