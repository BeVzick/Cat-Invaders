#include "Pointer.h"

Pointer::Pointer(sf::Texture &texture)
    : sprite(texture), state(PointerState::None)
{
    animationComponent = new AnimationComponent(sprite, {32, 32});

    animationComponent->AddAnimation("move_to", 0, 8, 100);
    animationComponent->AddAnimation("attack", 1, 8, 100);
    animationComponent->AddAnimation("defend", 2, 8, 100);
    animationComponent->AddAnimation("build", 3, 8, 100);

    sprite.setOrigin({32 * 0.5f, 32 * 0.5f});
}

void Pointer::Update(sf::Vector2f mouse_pos_world, float dt)
{
    sprite.setPosition(mouse_pos_world);

    switch (state)
    {
    case PointerState::Move:
        animationComponent->Play("move_to", dt);
        break;
    case PointerState::Attack:
        animationComponent->Play("attack", dt);
        break;
    case PointerState::Defend:
        animationComponent->Play("defend", dt);
        break;
    case PointerState::Build:
        animationComponent->Play("build", dt);
        break;
    }
}

void Pointer::Render(sf::RenderTarget& target)
{
    if (state != PointerState::None)
        target.draw(sprite);
}

PointerState Pointer::GetState()
{
    return state;
}

void Pointer::SetState(PointerState state)
{
    this->state = state;
}
