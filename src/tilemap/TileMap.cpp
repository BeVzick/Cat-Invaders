#include "TileMap.h"

TileMap::TileMap(sf::Vector3u size)
{
    tiles.resize(size.x);
    for (auto& x : tiles)
    {
        x.resize(size.y);
        for (auto& y : x)
            y.resize(size.z);
    }
}

TileMap::~TileMap()
{for (auto& x : tiles)
        for (auto& y: x)
            for (auto& z : y)
                delete z;
}

void TileMap::Update()
{
    for (auto& x : tiles)
        for (auto& y: x)
            for (auto& z : y)
                if (z != nullptr)
                    z->Update();
}

void TileMap::Render(sf::RenderTarget &target)
{
    for (auto& x : tiles)
        for (auto& y: x)
            for (auto& z : y)
                if (z != nullptr)
                    z->Render(target);
}

void TileMap::SetTile(sf::Vector3u pos, Tile* tile)
{
    delete tiles[pos.x][pos.y][pos.z];
    tiles[pos.x][pos.y][pos.z] = tile;
}
