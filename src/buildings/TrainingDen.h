#pragma once

#include "Building.h"
#include "../managers/ResourceManager.h"

class TrainingDen : public Building
{
public:
    TrainingDen(sf::Texture& texture, ResourceManager& resourceManager);
    ~TrainingDen();

private:
    ResourceManager& resourceManager;
};
