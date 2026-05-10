#include "Research.h"

Research::Research(unsigned research_time, std::string name, ResearchEffect effect)
    : researchTime(research_time), name(name), effect(effect)
{
}

Research::~Research()
{
}

bool Research::Tick(float dt)
{
    if (IsComplete())
        return true;
    elapsed += dt;
    if (elapsed >= static_cast<float>(researchTime))
    {
        elapsed = static_cast<float>(researchTime);
        complete = true;
    }
    return complete;
}

float Research::GetProgress() const
{
    return elapsed / static_cast<float>(researchTime);
}

bool Research::IsComplete() const
{
    return complete;
}

std::string Research::GetName() const
{
    return name;
}

unsigned Research::GetResearchTime() const
{
    return researchTime;
}

const ResearchEffect &Research::GetEffect() const
{
    return effect;
}

void Research::Reset()
{
    elapsed = 0.f;
    complete = false;
}
