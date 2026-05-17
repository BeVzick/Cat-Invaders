#include "Settings.h"

nlohmann::json Settings::Serialize()
{
    nlohmann::json settings;

    nlohmann::json general;
    general["show_fps"] = showFPS;
    general["language"] = language;

    nlohmann::json graphics;
    graphics["video_mode"] = {{"x", videoMode.size.x}, {"y", videoMode.size.y}};
    graphics["framerate_limit"] = framerateLimit;
    graphics["vertical_sync"] = verticalSync;
    graphics["fullscreen"] = fullscreen;
    graphics["anti_aliasing_level"] = antiAliasingLevel;

    nlohmann::json audio;
    audio["master_volume"] = masterVolume;
    audio["music_volume"] = musicVolume;

    settings["general"] = general;
    settings["graphics"] = graphics;
    settings["audio"] = audio;

    return settings;
}

void Settings::Deserialize(const nlohmann::json& data)
{
    // General
    showFPS = data["general"].value("show_fps", false);
    language = data["general"].value("language", "English");

    // Graphics
    int vmx = data["graphics"]["video_mode"].value("x", 0);
    int vmy = data["graphics"]["video_mode"].value("y", 0);
    videoMode = sf::VideoMode({vmx, vmy});
    framerateLimit = data["graphics"].value("framerate_limit", 120);
    verticalSync = data["graphics"].value("vertical_sync", false);
    fullscreen = data["graphics"].value("fullscreen", false);
    antiAliasingLevel = data["graphics"].value("anti_aliasing_level", 8);

    // Audio
    masterVolume = data["audio"].value("master_volume", 50);
    musicVolume = data["audio"].value("music_volume", 10);
}
