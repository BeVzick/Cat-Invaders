#pragma once

#include "IAction.h"

#include <SFML/System/Vector2.hpp>

class DefendAction : public IAction
{
public:
    DefendAction(sf::Vector2f posIso);
    ~DefendAction();

private:
    sf::Vector2f posIso;
};
