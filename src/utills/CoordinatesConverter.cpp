#include "CoordinatesConverter.h"

#include <SFML/Graphics/RenderWindow.hpp>

sf::Vector2f CoordinatesCovnverter::IsoToWorld(sf::Vector2f pos, sf::Vector2f grid_size)
{
    return {
        pos.x * 0.25 * grid_size.y + pos.y * 0.5 * grid_size.x,
        pos.x * -0.25 * grid_size.y + pos.y * 0.5 * grid_size.x
    };
}

sf::Vector2f CoordinatesCovnverter::WorldToIso(sf::Vector2f pos, sf::Vector2f grid_size)
{
    return {
        pos.x * 0.5 * grid_size.x + pos.y * -0.5 * grid_size.x,
        pos.x * 0.25 * grid_size.y + pos.y * 0.25 * grid_size.y
    };
}
