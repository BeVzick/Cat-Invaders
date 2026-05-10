#pragma once

#include "../Unit.h"
#include "../../../actions/ISkill.h"

class Hero : public Unit
{
public:
    Hero(sf::Texture& texture, sf::Vector2i frame_size = {32, 32});
    virtual ~Hero();

    void ShowData() override;
    void Update(sf::Vector2f mouse_pos_view, float dt) override;

    bool GetIsLeader() const;
    void SetIsLeader(bool is_leader);

    void AddSkill(ISkill* skill);
    const std::vector<ISkill*>& GetSkills() const;
    void ActivateSkill(unsigned index);

protected:
    bool isLeader;
    std::vector<ISkill*> skills; 
};
