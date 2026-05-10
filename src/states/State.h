#pragma once

#include "../Settings.h"
#include <stack>
#include <SFML/Graphics.hpp>
#include <imgui.h>

class State
{
public:
    State(sf::RenderWindow& window, std::vector<State*>& states, Settings& settings);
    virtual ~State();

    void UpdateMousePos();
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;

    bool GetQuit();
    void PushState(State* state);

    virtual void OnResize() {}

protected:
    Settings& settings;
    sf::RenderWindow& window;
    std::vector<State*>& states;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;
    sf::Vector2i mousePosIsoGrid;

    bool quit;

    static ImGuiWindowFlags fullscreenFlags;
};
