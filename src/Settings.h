#pragma once

#include "ISerializable.h"
#include <vector>
#include <string>
#include <SFML/Window/VideoMode.hpp>

struct Settings : public ISerializable {
    // General
    bool showFPS = false;
    std::vector<std::string> availableLanguages = {"English"};
    std::string language = "English";

    // Graphics
    std::vector<sf::VideoMode> videoModes;
    sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();
    std::vector<unsigned> availableFramerateLimits = {144, 120, 60, 30};
    unsigned framerateLimit = 120;
    bool verticalSync = false;
    bool fullscreen = false;
    std::vector<unsigned> availableAntiAliasingLevels = {8, 4, 2, 0};
    unsigned antiAliasingLevel = 8;

    // Audio
    int masterVolume = 50;
    int musicVolume = 10;

    nlohmann::json Serialize();
    void Deserialize(const nlohmann::json& data);
};
