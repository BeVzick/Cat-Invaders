#include "MainWindowState.h"

#include "GameState.h"
#include "SettingsState.h"
#include <imgui-SFML.h>

MainWindowState::MainWindowState(sf::RenderWindow& window, std::vector<State *>& states, Settings& settings)
    : State(window, states, settings)
{
}

MainWindowState::~MainWindowState()
{
}

void MainWindowState::Update(float dt)
{
    ImGui::SetNextWindowPos({});
    ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);

    ImGui::Begin("MainWindow", nullptr, fullscreenFlags);

    ImGui::SetWindowFontScale(3);
    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("Cat Invaders").x) / 2);
    ImGui::Text("Cat Invaders", ImGui::GetFontSize(), 64);
    ImGui::SetWindowFontScale(1);

    if (ImGui::Button("New Game", {250, 50}))
        PushState(new GameState(window, states, settings));

    if (ImGui::Button("Continue", {250, 50}))
        PushState(new GameState(window, states, settings));

    if (ImGui::Button("Settings", {250, 50}))
        PushState(new SettingsState(window, states, settings));

    if (ImGui::Button("Quit", {250, 50}))
        quit = true;

    ImGui::End();
}

void MainWindowState::Render()
{
}
