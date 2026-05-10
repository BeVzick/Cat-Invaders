#include "Hospital.h"

Hospital::Hospital(sf::Texture &texture)
    : Building(texture), slots(new Unit*[4]), healSpeed(1)
{
}

Hospital::~Hospital()
{
    delete[] slots;
}

void Hospital::AddToSlot(Unit *unit)
{
}

void Hospital::AddToSlots(std::vector<Unit *> &units)
{
}

void Hospital::RemoveFromSlot(unsigned index)
{
}

void Hospital::RemoveAllFromSlots()
{
}
