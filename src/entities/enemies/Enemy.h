#pragma once

#include "../Entity.h"

enum class EnemyType {
    RegularRat,
    Bat
};

class Enemy : public Entity
{
public:
    Enemy(sf::Texture& texture, sf::Vector2i frame_size = {32, 32});
    virtual ~Enemy();

protected:
    virtual std::string GetType() const override;
};
