#include "Building.h"

Building::Building(sf::Texture &texture)
    : GameObject(texture)
{
}

Building::~Building()
{
}

bool Building::IsDestroyed()
{
    return health == 0;
}

std::string Building::GetType() const
{
    return "Building";
}
