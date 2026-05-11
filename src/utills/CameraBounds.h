#pragma once

#include <SFML/Graphics/View.hpp>

class CameraBounds
{
public:
    static void SetMapSize(sf::Vector2u tile_count, sf::Vector2f tile_size);
    static void Clamp(sf::View& view);
    static sf::FloatRect GetBounds();

private:
    static float minX;
    static float minY;
    static float maxX;
    static float maxY;
};
