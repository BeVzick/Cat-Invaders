#include "SaveManager.h"

#include "../states/GameState.h"
#include <iomanip>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

unsigned long SaveManager::newID = 0;

SaveManager::SaveManager(const std::string& saveDir)
    : saveDir(saveDir)
{
    if (!fs::exists(saveDir))
        fs::create_directory(saveDir);

    nlohmann::json save;
    std::ifstream file(saveDir + "/save_slots.json");
    if (file.is_open())
        file >> save;
    file.close();

    newID = save.value("new_id", 0);
    lastSaveSlotID = save.value("last_save_id", -1);

    for (const auto& slotJson : save["slots"])
    {
        SaveSlot slot = SaveSlot(
            slotJson.value("id", 0),
            slotJson.value("name", ""),
            slotJson.value("filename", ""),
            slotJson.value("datetime", ""),
            slotJson.value("time_played", 0)
        );
        slots.push_back(slot);
    }
}

SaveManager::~SaveManager()
{
    nlohmann::json save;
    save["new_id"] = newID;
    save["last_save_id"] = lastSaveSlotID;
    save["slots"] = nlohmann::json::array();

    for (auto& slot : slots)
        save["slots"].push_back(slot.Serialize());

    std::ofstream file(saveDir + "/save_slots.json");
    if (file.is_open())
        file << save.dump(4);
    file.close();
}

std::vector<SaveSlot> SaveManager::GetSlots()
{
    return slots;
}

void SaveManager::DeleteSlot(unsigned index)
{
    std::string fullPath = saveDir + '/' + slots[index].GetFilename();
    if (fs::exists(fullPath))
        fs::remove(fullPath);
    slots.erase(slots.begin() + index);
}

bool SaveManager::SaveGame(unsigned index, const nlohmann::json& game_state_data)
{
    std::string fullPath = saveDir + '/' + slots[index].GetFilename();
    lastSaveSlotID = slots[index].GetID();
    slots[index].SetDatetime(GetCurrentDateTime());
    std::ofstream file(fullPath);
    if (file.is_open())
    {
        file << game_state_data.dump(4);
        return true;
    }
    return false;
}

void SaveManager::LoadGame(unsigned index, GameState& state)
{
    std::string fullPath = saveDir + '/' + slots[index].GetFilename();
    std::ifstream file(fullPath);
    nlohmann::json save;
    if (file.is_open())
    {
        try
        {
            file >> save;
            state.Deserialize(save);
        }
        catch (nlohmann::json::parse_error& e)
        {
            std::cerr << "Parsing json error: " << e.what() << '\n';
        }
    }
}

void SaveManager::LoadLastGame(GameState &state)
{
    SaveSlot* slot = nullptr;
    for (auto& s : slots)
        if (s.GetID() == lastSaveSlotID)
            slot = &s;

    if (!slot)
        return;

    std::string fullPath = saveDir + '/' + slot->GetFilename();
    std::ifstream file(fullPath);
    nlohmann::json save;
    if (file.is_open())
    {
        try
        {
            file >> save;
            state.Deserialize(save);
        }
        catch (nlohmann::json::parse_error& e)
        {
            std::cerr << "Parsing json error: " << e.what() << '\n';
        }
    }
}

void SaveManager::NewSlot(const std::string &name)
{
    std::string datetime = GetCurrentDateTime();
    SaveSlot slot = SaveSlot(newID++, name, name + '_' + datetime, datetime, 0);
    slots.push_back(slot);
}

std::string SaveManager::FormatTimePlayed(std::time_t time)
{
    int hours = time / 3600;
    int minutes = (time % 3600) / 60;
    int seconds = time % 60;

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << hours << ':'
        << std::setfill('0') << std::setw(2) << minutes << ':'
        << std::setfill('0') << std::setw(2) << seconds;
    return oss.str();
}

std::string SaveManager::GetCurrentDateTime()
{
    std::time_t now = std::time(nullptr);
    std::tm tm = *std::localtime(&now);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y %H:%M:%S");

    return oss.str();
}
