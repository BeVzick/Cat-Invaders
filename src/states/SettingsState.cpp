#include "SettingsState.h"

#include <imgui-SFML.h>

SettingsState::SettingsState(sf::RenderWindow& window, std::vector<State *>& states, Settings& settings)
    : State(window, states, settings), newSettings(settings), shouldReloadWindow(false)
{
}

SettingsState::~SettingsState()
{
}

void SettingsState::Update(float dt)
{
    ImGui::SetNextWindowPos({});
    ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);

    ImGui::Begin("SettingsState", nullptr, fullscreenFlags);

    if (ImGui::BeginTabBar("SettingsTabBar"))
    {
        if (ImGui::BeginTabItem("General"))
        {
            if (ImGui::BeginCombo("Language", newSettings.language.c_str()))
            {
                for (int i = 0; i < newSettings.availableLanguages.size(); ++i)
                {
                    bool isSelected = newSettings.language == newSettings.availableLanguages[i];
                    if (ImGui::Selectable(newSettings.availableLanguages[i].c_str(), isSelected))
                        newSettings.language = newSettings.availableLanguages[i];
                }

                ImGui::EndCombo();
            }

            ImGui::Checkbox("Show FPS", &newSettings.showFPS);

            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Graphics"))
        {
            std::string resolution =
                std::to_string(newSettings.videoMode.size.x)
                + "x" +
                std::to_string(newSettings.videoMode.size.y);
            if (ImGui::BeginCombo("Resolution", resolution.c_str()))
            {
                for (int i = 0; i < newSettings.videoModes.size(); ++i)
                {
                    bool isSelected = newSettings.videoModes[i] == settings.videoMode;
                    std::string resolution =
                        std::to_string(newSettings.videoModes[i].size.x)
                        + "x" +
                        std::to_string(newSettings.videoModes[i].size.y);
                    if (ImGui::Selectable(resolution.c_str(), isSelected))
                        newSettings.videoMode = newSettings.videoModes[i];
                }

                ImGui::EndCombo();
            }

            if (ImGui::BeginCombo("Framerate Limit", std::to_string(newSettings.framerateLimit).c_str()))
            {
                for (int i = 0; i < newSettings.availableFramerateLimits.size(); ++i)
                {
                    bool isSelected = newSettings.framerateLimit == newSettings.availableFramerateLimits[i];
                    if (ImGui::Selectable(std::to_string(newSettings.availableFramerateLimits[i]).c_str(), isSelected))
                        newSettings.framerateLimit = newSettings.availableFramerateLimits[i];
                }

                ImGui::EndCombo();
            }

            ImGui::Checkbox("Vertical Sync", &newSettings.verticalSync);

            ImGui::Checkbox("Fullscreen", &newSettings.fullscreen);

            if (ImGui::BeginCombo("AntiAliasing Level", std::to_string(newSettings.antiAliasingLevel).c_str()))
            {
                for (int i = 0; i < newSettings.availableAntiAliasingLevels.size(); ++i)
                {
                    bool isSelected = newSettings.antiAliasingLevel == newSettings.availableAntiAliasingLevels[i];
                    if (ImGui::Selectable(std::to_string(newSettings.availableAntiAliasingLevels[i]).c_str(), isSelected))
                        newSettings.antiAliasingLevel = newSettings.availableAntiAliasingLevels[i];
                }

                ImGui::EndCombo();
            }

            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Audio"))
        {
            ImGui::SliderInt("Master Volume", &newSettings.masterVolume, 0, 100, "%d%%");
            ImGui::SliderInt("Music Volume", &newSettings.musicVolume, 0, 100, "%d%%");

            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Keybinds"))
        {
            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }
    ImGui::Separator();

    if (ImGui::Button("Apply", {250, 50}))
    {
        if (settings.antiAliasingLevel != newSettings.antiAliasingLevel ||
            settings.framerateLimit != newSettings.framerateLimit ||
            settings.fullscreen != newSettings.fullscreen ||
            settings.language != newSettings.language ||
            settings.verticalSync != newSettings.verticalSync ||
            settings.videoMode != newSettings.videoMode)
            shouldReloadWindow = true;

        settings = newSettings;
    }
    ImGui::SameLine();
    if (ImGui::Button("Close", {250, 50}))
        quit = true;

    ImGui::End();
}

void SettingsState::Render()
{
}

bool SettingsState::GetShouldReloadWindow()
{
    return shouldReloadWindow;
}

void SettingsState::ResetShouldReloadWindow()
{
    shouldReloadWindow = false;
}
