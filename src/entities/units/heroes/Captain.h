#pragma once

#include "Hero.h"

class Captain : public Hero
{
public:
    Captain(sf::Texture& texture);
    ~Captain();

protected:
    std::string GetType() const override;
};
