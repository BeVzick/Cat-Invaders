#pragma once

#include "../SaveSlot.h"
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

class GameState;

class SaveManager
{
public:
    SaveManager(const std::string& saveDir = "saves");
    ~SaveManager();

    bool SaveGame(unsigned index, const nlohmann::json& game_state_data);
    void LoadGame(unsigned index, GameState& state);
    void NewSlot(const std::string& name);
    std::vector<SaveSlot> GetSlots();
    void DeleteSlot(unsigned index);

    static std::string FormatTimePlayed(std::time_t time);

private:
    std::vector<SaveSlot> slots;
    std::string saveDir;

    static unsigned newID;

    std::string GetCurrentDateTime();
};
