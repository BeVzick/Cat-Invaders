#include "Captain.h"

Captain::Captain(sf::Texture &texture)
    : Hero(texture, {32, 32})
{
    animationComponent->AddAnimation("default", 0, 4, {500, 100, 500, 150});
    animationComponent->AddAnimation("default-selected", 1, 4, {500, 100, 500, 150});
    animationComponent->AddAnimation("walk_down", 2, 4, 150);
    animationComponent->AddAnimation("walk_down-selected", 3, 4, 150);
    animationComponent->AddAnimation("walk_down_left", 4, 4, 150);
    animationComponent->AddAnimation("walk_down_left-selected", 5, 4, 150);
    animationComponent->AddAnimation("walk_left", 6, 4, 150);
    animationComponent->AddAnimation("walk_left-selected", 7, 4, 150);
    animationComponent->AddAnimation("walk_up_left", 8, 4, 150);
    animationComponent->AddAnimation("walk_up_left-selected", 9, 4, 150);
    animationComponent->AddAnimation("walk_up", 10, 4, 150);
    animationComponent->AddAnimation("walk_up-selected", 11, 4, 150);
    animationComponent->AddAnimation("walk_up_right", 12, 4, 150);
    animationComponent->AddAnimation("walk_up_right-selected", 13, 4, 150);
    animationComponent->AddAnimation("walk_right", 14, 4, 150);
    animationComponent->AddAnimation("walk_right-selected", 15, 4, 150);
    animationComponent->AddAnimation("walk_down_right", 16, 4, 150);
    animationComponent->AddAnimation("walk_down_right-selected", 17, 4, 150);

    maxHealth = 500;
    health = maxHealth;
    damage = 20;
    attackSpeed = 1.5f;
    speed = 25.f;
}

Captain::~Captain()
{
}

std::string Captain::GetType() const
{
    return "Captain";
}
