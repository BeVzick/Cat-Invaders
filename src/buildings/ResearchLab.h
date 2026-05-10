#pragma once

#include "Building.h"
#include "../managers/ResearchManager.h"

class ResearchLab : public Building
{
public:
    ResearchLab(sf::Texture& texture, ResearchManager& researchManager);
    ~ResearchLab();

private:
    ResearchManager& researchManager;
    unsigned researchSpeed;
};
