#pragma once

#include "State.h"


class SettingsState : public State
{
public:
    SettingsState(sf::RenderWindow& window, std::vector<State*>& states, Settings& settings);
    ~SettingsState();

    void Update(float dt) override;
    void Render() override;

    bool GetShouldReloadWindow();
    void ResetShouldReloadWindow();

private:
    Settings newSettings;
    bool shouldReloadWindow;
};
