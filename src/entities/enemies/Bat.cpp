#include "Bat.h"

#include <SFML/Window/Keyboard.hpp>

Bat::Bat(sf::Texture &texture)
    : Enemy(texture, {48, 32})
{
    animationComponent->AddAnimation("default", 0, 5, {200, 150, 150, 200, 200});
    animationComponent->AddAnimation("walk_down", 1, 5, {150, 100, 100, 150, 150});
    animationComponent->AddAnimation("walk_left", 3, 5, {150, 100, 100, 150, 150});
    animationComponent->AddAnimation("walk_up", 5, 5, {150, 100, 100, 150, 150});
    animationComponent->AddAnimation("walk_right", 7, 5, {150, 100, 100, 150, 150});

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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad2))
            animationComponent->Play("walk_down", dt);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad8))
            animationComponent->Play("walk_up", dt);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad4))
            animationComponent->Play("walk_left", dt);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad6))
            animationComponent->Play("walk_right", dt);
        else
            animationComponent->Play("default", dt);
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
