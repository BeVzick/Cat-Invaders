#include "Enemy.h"

Enemy::Enemy(sf::Texture &texture, sf::Vector2i frame_size)
    : Entity(texture, frame_size)
{
}

Enemy::~Enemy()
{
}

std::string Enemy::GetType() const
{
    return "Enemy";
}
