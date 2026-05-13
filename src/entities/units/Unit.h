#pragma once

#include "../Entity.h"

class Unit : public Entity
{
public:
    Unit(sf::Texture& texture, sf::Vector2i frame_size = {32, 32}, bool has_group = false);
    virtual ~Unit();

    void ShowData() override;
    void UpdateAnimations(float dt) override;

    bool GetHasGroup();
    void SetHasGroup(bool has_group);

protected:
    unsigned trainingTime;
    bool hasGroup;

    std::string GetType() const override;
};
