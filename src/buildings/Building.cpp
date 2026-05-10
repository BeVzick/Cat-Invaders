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
