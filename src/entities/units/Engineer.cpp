#include "Engineer.h"

#include <string>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <random>

Engineer::Engineer(sf::Texture& texture)
    : Unit(texture, {32, 32})
{
    animationComponent->AddAnimation("default", 0, 4, {500, 150, 500, 150});
    animationComponent->AddAnimation("default-selected", 1, 4, {500, 150, 500, 150});
    animationComponent->AddAnimation("idle1", 2, 14, {100, 150, 150, 300, 150, 300, 150, 150, 150, 300, 150, 300, 150, 150});
    animationComponent->AddAnimation("idle1-selected", 3, 14, {100, 150, 150, 300, 150, 300, 150, 150, 150, 300, 150, 300, 150, 150});
    animationComponent->AddAnimation("idle2", 4, 4, {200, 750, 200, 750});
    animationComponent->AddAnimation("idle2-selected", 5, 4, {200, 750, 200, 750});
    animationComponent->AddAnimation("walk_down", 6, 4, 100);
    animationComponent->AddAnimation("walk_down-selected", 7, 4, 100);
    animationComponent->AddAnimation("walk_down_left", 8, 4, 100);
    animationComponent->AddAnimation("walk_down_left-selected", 9, 4, 100);
    animationComponent->AddAnimation("walk_left", 10, 4, 100);
    animationComponent->AddAnimation("walk_left-selected", 11, 4, 100);
    animationComponent->AddAnimation("walk_up_left", 12, 4, 100);
    animationComponent->AddAnimation("walk_up_left-selected", 13, 4, 100);
    animationComponent->AddAnimation("walk_up", 14, 4, 100);
    animationComponent->AddAnimation("walk_up-selected", 15, 4, 100);
    animationComponent->AddAnimation("walk_up_right", 16, 4, 100);
    animationComponent->AddAnimation("walk_up_right-selected", 17, 4, 100);
    animationComponent->AddAnimation("walk_right", 18, 4, 100);
    animationComponent->AddAnimation("walk_right-selected", 19, 4, 100);
    animationComponent->AddAnimation("walk_down_right", 20, 4, 100);
    animationComponent->AddAnimation("walk_down_right-selected", 21, 4, 100);

    maxHealth = 50;
    health = maxHealth;
    damage = 5;
    attackSpeed = 1.f;
    speed = 30.f;

    trainingTime = 15;
}

Engineer::~Engineer()
{
}

std::string Engineer::GetType() const
{
    return "Engineer";
}
