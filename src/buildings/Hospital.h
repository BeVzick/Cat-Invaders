#pragma once

#include "Building.h"
#include "../entities/units/Unit.h"
#include <vector>

class Hospital : public Building
{
public:
    Hospital(sf::Texture& texture);
    ~Hospital();

    void AddToSlot(Unit* unit);
    void AddToSlots(std::vector<Unit*>& units);
    void RemoveFromSlot(unsigned index);
    void RemoveAllFromSlots();

private:
    Unit** slots;
    unsigned healSpeed;
};
