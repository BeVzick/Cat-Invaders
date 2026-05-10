#include "State.h"

ImGuiWindowFlags State::fullscreenFlags = ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoBackground;

State::State(sf::RenderWindow& window, std::vector<State *>& states, Settings& settings)
    : window(window), states(states),  settings(settings), quit(false)
{
}

State::~State()
{
}

void State::UpdateMousePos()
{
    mousePosWindow = sf::Mouse::getPosition(window);
    mousePosView = window.mapPixelToCoords(mousePosWindow, window.getView());
}

bool State::GetQuit()
{
    return quit;
}

void State::PushState(State *state)
{
    states.push_back(state);
}
