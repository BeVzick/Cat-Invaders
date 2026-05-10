#include "Hero.h"

Hero::Hero(sf::Texture &texture, sf::Vector2i frame_size)
    : Unit(texture, frame_size)
{
}

Hero::~Hero()
{
}

void Hero::ShowData()
{
    Entity::ShowData();
}

bool Hero::GetIsLeader()
{
    return isLeader;
}

void Hero::SetIsLeader(bool is_leader)
{
    isLeader = is_leader;
}
