#pragma once

#include "State.h"
#include <imgui.h>

class MainWindowState : public State
{
public:
    MainWindowState(sf::RenderWindow& window, std::vector<State*>& states, Settings& settings);
    ~MainWindowState();

    void Update(float dt) override;
    void Render() override;
};
