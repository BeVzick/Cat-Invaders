#include "Hero.h"

Hero::Hero(sf::Texture &texture, sf::Vector2i frame_size)
    : Unit(texture, frame_size)
{
}

Hero::~Hero()
{
}

void Hero::ShowData()
{
    Entity::ShowData();
}

void Hero::Update(sf::Vector2f mouse_pos_view, float dt)
{
    Unit::Update(mouse_pos_view, dt);

    for (auto* s : skills)
        s->Update(dt);
}

bool Hero::GetIsLeader() const
{
    return isLeader;
}

void Hero::SetIsLeader(bool is_leader)
{
    isLeader = is_leader;
}

void Hero::AddSkill(ISkill *skill)
{
    skills.push_back(skill);
}

const std::vector<ISkill *> &Hero::GetSkills() const
{
    return skills;
}

void Hero::ActivateSkill(unsigned index)
{
    if (index < skills.size())
        skills[index]->Activate(*this);
}

std::string Hero::GetType() const
{
    return "Hero";
}
