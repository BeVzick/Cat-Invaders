#include "Scratcher.h"

Scratcher::Scratcher(sf::Texture &texture)
    : Unit(texture)
{
}

Scratcher::~Scratcher()
{
}

std::string Scratcher::GetType() const
{
    return "Scratcher";
}
