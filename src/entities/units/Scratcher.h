#pragma once

#include "Unit.h"

class Scratcher : public Unit
{
public:
    Scratcher(sf::Texture& texture);
    ~Scratcher();

protected:
    virtual std::string GetType() const override;
};
