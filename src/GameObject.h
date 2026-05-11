#pragma once

#include "utills/AnimationComponent.h"

class ProfileManager;

class GameObject
{
    friend ProfileManager;
public:
    GameObject(sf::Texture& texture, sf::Vector2i frame_size = {32, 32}, sf::Vector2f pos = {});
    virtual ~GameObject();

    virtual void ShowData();
    virtual void UpdateAnimations(float dt) = 0;
    virtual void Update(sf::Vector2f mouse_pos_view, const float dt);
    virtual void Render(sf::RenderTarget& target);

    sf::Vector2f GetPos() const;
    unsigned GetHealth() const;
    bool GetIsSelected() const;

    void SetPos(sf::Vector2f pos);
    void SetIsSelected(bool is_selected);

    void TakeDamage(unsigned damage);

protected:
    AnimationComponent* animationComponent;
    unsigned health;
    unsigned maxHealth;
    bool isSelected;

private:
    sf::Sprite sprite;
    sf::Vector2f pos;
};
