#pragma once

#include "ResearchEffect.h"

class Research
{
public:
    Research(unsigned research_time, std::string name, ResearchEffect effect);
    virtual ~Research();

    bool Tick(float dt);

    float GetProgress() const;
    bool IsComplete() const;
    std::string GetName() const;
    unsigned GetResearchTime() const;
    const ResearchEffect& GetEffect() const;

    void Reset();

protected:
    unsigned researchTime;
    float elapsed;
    bool complete;
    std::string name;
    ResearchEffect effect;
};
