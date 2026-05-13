#pragma once

#include "utills/AnimationComponent.h"
#include <nlohmann/json.hpp>

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

    static void InitNewID(unsigned long new_id);

    unsigned long GetID() const;
    sf::Vector2f GetPos() const;
    unsigned GetHealth() const;
    bool GetIsSelected() const;

    void SetPos(sf::Vector2f pos);
    void SetIsSelected(bool is_selected);

    void TakeDamage(unsigned damage);

    virtual nlohmann::json Serialize();
    virtual void Deserialize(const nlohmann::json& data);

protected:
    AnimationComponent* animationComponent;
    unsigned long id;
    unsigned health;
    unsigned maxHealth;
    bool isSelected;

    virtual std::string GetType() const;

private:
    sf::Sprite sprite;
    sf::Vector2f pos;

    static unsigned long newID;
};
