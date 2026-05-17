#pragma once

#include "Tile.h"
#include <vector>
#include <SFML/System/Vector3.hpp>
#include <nlohmann/json.hpp>

class TileMap
{
public:
    TileMap(sf::Vector3u size = {});
    ~TileMap();

    void SetTile(sf::Vector3u pos, Tile* tile);

    void Update();
    void Render(sf::RenderTarget& target);

private:
    std::vector<std::vector<std::vector<Tile*>>> tiles;
};
