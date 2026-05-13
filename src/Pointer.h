#pragma once

#include "utills/AnimationComponent.h"
#include <SFML/Graphics/RenderTarget.hpp>

enum class PointerState {
    None, Move, Attack, Defend, Build
};

class Pointer
{
public:
    Pointer(sf::Texture& texture);

    void Update(sf::Vector2f mouse_pos_world, float dt);
    void Render(sf::RenderTarget& target);

    PointerState GetState();
    void SetState(PointerState state);

private:
    sf::Sprite sprite;
    AnimationComponent* animationComponent;
    PointerState state;
    bool isPointerShow;
};
