#pragma once

#include "../GameObject.h"

class Building : public GameObject
{
public:
    Building(sf::Texture& texture);
    virtual ~Building();

    bool IsDestroyed();

protected:
    unsigned level;
    unsigned maxLevel;
    bool isCompleted;

    std::string GetType() const override;
};

