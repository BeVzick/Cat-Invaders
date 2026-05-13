#include "GameObject.h"

#include "utills/CoordinatesConverter.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <string>
#include <imgui.h>

unsigned long GameObject::newID = 0;

GameObject::GameObject(sf::Texture& texture, sf::Vector2i frame_size, sf::Vector2f pos)
    : sprite(texture), pos(pos), isSelected(false), id(newID++)
{
    animationComponent = new AnimationComponent(sprite, frame_size);

    sprite.setOrigin({frame_size.x * 0.5f, frame_size.y * 0.5f});
    sprite.setPosition(pos);
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

void GameObject::InitNewID(unsigned long new_id)
{
    newID = new_id;
}

unsigned long GameObject::GetID() const
{
    return id;
}

sf::Vector2f GameObject::GetPos() const
{
    return pos;
}

unsigned GameObject::GetHealth() const
{
    return health;
}

bool GameObject::GetIsSelected() const
{
    return isSelected;
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

void GameObject::TakeDamage(unsigned damage)
{
    damage = std::min(health, damage);
    health -= damage;
}

nlohmann::json GameObject::Serialize()
{
    nlohmann::json object = nlohmann::json::object();

    object["id"] = id;
    object["type"] = GetType();
    object["pos"] = {{"x", pos.x}, {"y", pos.y}}; 
    object["health"] = health;
    object["selected"] = isSelected;

    return object;
}

void GameObject::Deserialize(const nlohmann::json &data)
{
    id = data["id"];
    float px = data["pos"].value("x", 0.f);
    float py = data["pos"].value("y", 0.f);
    SetPos({px, py});
    health = data.value("health", maxHealth);
    isSelected = data.value("selecteed", false);
}

std::string GameObject::GetType() const
{
    return "GameObject";
}
