#pragma once

#include "Unit.h"

class IronPaw : public Unit
{
public:
    IronPaw(sf::Texture& texture);
    ~IronPaw();

protected:
    virtual std::string GetType() const override;
};
