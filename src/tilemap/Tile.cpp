#include "Tile.h"

#include "../utills/CoordinatesConverter.h"
#include <SFML/Graphics/RenderTarget.hpp>

Tile::Tile(sf::Texture &texture, sf::IntRect rect, sf::Vector2f pos_iso)
    : texture(texture), posIso(pos_iso)
{
    shape = sf::RectangleShape(sf::Vector2f(rect.size));
    shape.setOrigin({shape.getSize().x / 2.f, 0});
    shape.setTextureRect(rect);
    shape.setTexture(&texture);
    shape.setPosition(posIso);
}

Tile::~Tile()
{
}

void Tile::Update()
{
}

void Tile::Render(sf::RenderTarget &target)
{
    target.draw(shape);
}
