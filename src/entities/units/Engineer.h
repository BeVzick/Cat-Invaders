#pragma once

#include "Unit.h"

class Engineer : public Unit
{
public:
    Engineer(sf::Texture& texture);
    ~Engineer();

protected:
    std::string GetType() const override;
};
