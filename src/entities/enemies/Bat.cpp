#include "Bat.h"

#include <SFML/Window/Keyboard.hpp>

Bat::Bat(sf::Texture &texture)
    : Enemy(texture, {48, 32})
{
    animationComponent->AddAnimation("default", 0, 5, {200, 150, 150, 200, 200});
    animationComponent->AddAnimation("default-selected", 1, 5, {200, 150, 150, 200, 200});
    animationComponent->AddAnimation("walk_down", 0, 5, {150, 100, 100, 150, 150});
    animationComponent->AddAnimation("walk_down-selected", 1, 5, {150, 100, 100, 150, 150});
    animationComponent->AddAnimation("walk_left", 4, 5, {150, 100, 100, 150, 150});
    animationComponent->AddAnimation("walk_left-selected", 5, 5, {150, 100, 100, 150, 150});
    animationComponent->AddAnimation("walk_up", 8, 5, {150, 100, 100, 150, 150});
    animationComponent->AddAnimation("walk_up-selected", 9, 5, {150, 100, 100, 150, 150});
    animationComponent->AddAnimation("walk_right-selected", 12, 5, {150, 100, 100, 150, 150});

    maxHealth = 50;
    health = maxHealth;
}

Bat::~Bat()
{
}

void Bat::UpdateAnimations(float dt)
{
    if (animationComponent)
    {
        std::string animation = "default";

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad2))
            animation = "walk_down";
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad8))
            animation = "walk_up";
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad4))
            animation = "walk_left";
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad6))
            animation = "walk_right";

        if (isSelected)
            animation.append("-selected");

            animationComponent->Play(animation, dt);
    }
}

void Bat::Update(sf::Vector2f mousePosView, float dt)
{
    Entity::Update(mousePosView, dt);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad2))
        SetPos(GetPos() + sf::Vector2f(0.f, 50.f) * dt);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad8))
        SetPos(GetPos() + sf::Vector2f(0.f, -50.f) * dt);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad4))
        SetPos(GetPos() + sf::Vector2f(-100.f, 0.f) * dt);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad6))
        SetPos(GetPos() + sf::Vector2f(100.f, 0.f) * dt);
}

std::string Bat::GetType() const
{
    return "Bat";
}
