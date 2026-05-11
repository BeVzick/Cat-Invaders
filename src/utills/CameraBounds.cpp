#include "CameraBounds.h"

#include <algorithm>

float CameraBounds::minX;
float CameraBounds::minY;
float CameraBounds::maxX;
float CameraBounds::maxY;

void CameraBounds::SetMapSize(sf::Vector2u tile_count, sf::Vector2f tile_size)
{
    float halfWidth = tile_size.x * 0.5f;
    float halfHeight = tile_size.y * 0.5f;

    float mapWidthPx = tile_count.x * halfWidth;
    float mapHeightPx = tile_count.y * halfWidth;

    float marginX = tile_size.x * 2.f;
    float marginY = tile_size.y * 2.f;

    minX = -mapHeightPx - marginX;
    maxX = mapWidthPx + marginX;

    minY = -marginY;
    maxY = (tile_count.x + tile_count.y) * halfHeight + marginY;
}

void CameraBounds::Clamp(sf::View &view)
{
    sf::Vector2f half = view.getSize() * 0.5f;
    sf::Vector2f c = view.getCenter();

    c.x = std::clamp(c.x, minX + half.x, maxX - half.x);
    c.y = std::clamp(c.y, minY + half.y, maxY - half.y);

    view.setCenter(c);
}

sf::FloatRect CameraBounds::GetBounds()
{
    return {{minX, minY}, {maxX - minX, maxY - minY}};
}
