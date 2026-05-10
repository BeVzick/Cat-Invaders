#pragma once

#include "states/State.h"
#include <stack>
#include <algorithm>
#include <SFML/Graphics.hpp>

class Game
{
public:
    Game();
    ~Game();

    void Run();

private:
    Settings settings;

    sf::RenderWindow* window;
    std::vector<State*> states;
    sf::Clock deltaClock;

    void Update();
    void Render();
    void ReloadWindow();
};
