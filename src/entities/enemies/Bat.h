#pragma once

#include "Enemy.h"

class Bat : public Enemy
{
public:
    Bat(sf::Texture& texture);
    ~Bat();

    void UpdateAnimations(float dt) override;
    void Update(sf::Vector2f mousePosView, float dt) override;

protected:
    std::string GetType() const override;
};
