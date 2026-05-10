#pragma once

#include "Enemy.h"

class RegularRat : public Enemy
{
public:
    RegularRat(sf::Texture& texture);
    ~RegularRat();
};
