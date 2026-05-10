#pragma once

#include "../Unit.h"

class Hero : public Unit
{
public:
    Hero(sf::Texture& texture, sf::Vector2i frame_size = {32, 32});
    virtual ~Hero();

    void ShowData() override;

    bool GetIsLeader();
    void SetIsLeader(bool is_leader);

protected:
    bool isLeader;
};
