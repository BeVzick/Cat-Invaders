#pragma once

#include <SFML/System/Vector2.hpp>

class CoordinatesCovnverter
{
public:
    CoordinatesCovnverter() = delete;

    static sf::Vector2f IsoToWorld(sf::Vector2f pos, sf::Vector2f grid_size);
    static sf::Vector2f WorldToIso(sf::Vector2f pos, sf::Vector2f grid_size);
};
