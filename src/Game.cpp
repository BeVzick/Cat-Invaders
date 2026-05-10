#include "Game.h"

#include "states/MainWindowState.h"
#include "states/SettingsState.h"
#include <algorithm>
#include <imgui.h>
#include <imgui_internal.h>
#include <imgui-SFML.h>
#include <iostream>

Game::Game()
{
    std::vector<sf::VideoMode> videoModes = sf::VideoMode::getFullscreenModes();
    std::sort(videoModes.begin(), videoModes.end(), 
        [](const auto& a, const auto& b) {
            if (a.size.x != b.size.x)
                return a.size.x > b.size.x;
            return a.size.y > b.size.y;
        }
    );
    videoModes.erase(
        std::unique(videoModes.begin(), videoModes.end(),
            [](auto& a, auto& b) { return a.size.x == b.size.x && a.size.y == b.size.y; }),
        videoModes.end()
    );
    settings.videoModes = videoModes;

    sf::State state = (settings.fullscreen) ? sf::State::Fullscreen : sf::State::Windowed;
    sf::ContextSettings ctx;
    ctx.antiAliasingLevel = settings.antiAliasingLevel;
    
    window = new sf::RenderWindow(settings.videoMode, "Cat Invaders", sf::Style::Close | sf::Style::Titlebar, state, ctx);
    window->setVerticalSyncEnabled(settings.verticalSync);
    window->setFramerateLimit(120);
    ImGui::SFML::Init(*window);

    states.push_back(new MainWindowState(*window, states, settings));
}

Game::~Game()
{
    while (!states.empty())
    {
        delete states.back();
        states.pop_back();
    }
    delete window;
}

void Game::Run()
{
    if (window == nullptr)
        return;

    while (window->isOpen())
    {
        Update();
        Render();
    }

    ImGui::SFML::Shutdown();
}

void Game::ReloadWindow()
{    
    sf::State state = (settings.fullscreen) ? sf::State::Fullscreen : sf::State::Windowed;
    sf::ContextSettings ctx;
    ctx.antiAliasingLevel = settings.antiAliasingLevel;

    window->create(settings.videoMode, "Cat Invaders", sf::Style::Close | sf::Style::Titlebar, state, ctx);
    ImGui::SFML::Shutdown();

    window->setVerticalSyncEnabled(settings.verticalSync);
    if (!settings.verticalSync)
        window->setFramerateLimit(settings.framerateLimit);

    ImGui::SFML::Init(*window);
}

void Game::Update()
{
    sf::Time dtTime = deltaClock.restart();
    float dt = dtTime.asSeconds();

    if (!states.empty())
    {
        SettingsState* settingsState = dynamic_cast<SettingsState*>(states.back());
        if (settingsState && settingsState->GetShouldReloadWindow())
        {
            ReloadWindow();
            for (auto* state : states)
                state->OnResize();
            settingsState->ResetShouldReloadWindow();
        }
    }

    while (std::optional<sf::Event> event = window->pollEvent())
    {
        ImGui::SFML::ProcessEvent(*window, event.value());

        if (event->is<sf::Event::Closed>())
            window->close();
    }

    ImGui::SFML::Update(*window, dtTime);
    
    if (!states.empty())
    {
        State* currState = states.back();
        currState->UpdateMousePos();
        currState->Update(dt);

        if (currState->GetQuit())
        {
            delete currState;
            states.pop_back();
        }
    }
    else
        window->close();
}

void Game::Render()
{
    if (window && window->isOpen())
    {
        window->clear();
        if (!states.empty())
            states.back()->Render();

        ImGui::SFML::Render(*window);
        
        window->display();
    }
}
