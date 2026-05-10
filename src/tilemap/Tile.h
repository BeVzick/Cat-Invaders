#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class Tile
{
public:
    Tile(sf::Texture& texture, sf::IntRect rect, sf::Vector2f pos_iso);
    ~Tile();

    void Update();
    void Render(sf::RenderTarget& target);

private:
    sf::Texture& texture;
    sf::RectangleShape shape;
    sf::Vector2f posIso;
};
