#include "ResearchLab.h"

ResearchLab::ResearchLab(sf::Texture &texture, ResearchManager &researchManager)
    : Building(texture), researchManager(researchManager), researchSpeed(1)
{
}

ResearchLab::~ResearchLab()
{
}
