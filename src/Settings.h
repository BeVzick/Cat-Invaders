    #pragma once

#include <vector>
#include <string>
#include <SFML/Window/VideoMode.hpp>

struct Settings {
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
    bool fullscreen = true;
    std::vector<unsigned> availableAntiAliasingLevels = {8, 4, 2, 0};
    unsigned antiAliasingLevel = 8;

    // Audio
    unsigned masterVolume = 25;
    unsigned musicVolume = 100;
};
