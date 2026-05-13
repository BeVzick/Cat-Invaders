#include "IronPaw.h"

IronPaw::IronPaw(sf::Texture &texture)
    : Unit(texture)
{
}

IronPaw::~IronPaw()
{
}

std::string IronPaw::GetType() const
{
    return "IronPaw";
}
