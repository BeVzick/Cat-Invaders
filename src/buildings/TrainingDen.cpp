#include "TrainingDen.h"

TrainingDen::TrainingDen(sf::Texture &texture, ResourceManager &resourceManager)
    : Building(texture), resourceManager(resourceManager)
{
}

TrainingDen::~TrainingDen()
{
}
