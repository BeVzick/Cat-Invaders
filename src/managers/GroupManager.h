#pragma once

#include "SelectionManager.h"
#include "ProfileManager.h"
#include "../entities/units/heroes/Hero.h"
#include <set>
#include <nlohmann/json.hpp>

class Group
{
public:
    Group(std::string name, Hero* leader = nullptr);
    ~Group();

    std::string GetName();
    Hero* const GetLeader();
    const std::set<Unit*>& GetUnits();

    void SetName(std::string name);
    void SetLeader(Hero* leader);
    void RemoveLeader();
    void AddToGroup(Unit* unit);
    void RemoveFropGroup(Unit* unit);

    nlohmann::json Serialize();

private:
    std::string name;
    Hero* leader;
    std::set<Unit*> units;
};

class GroupManager
{
    friend Group;
public:
    GroupManager(std::map<std::string, sf::Texture*>& textures, SelectionManager& selection_manager, ProfileManager& profile_manager);
    ~GroupManager();

    void UpdateUI();

    unsigned GetNewGroupID();
    void SetNewGroupID(unsigned id);

    const Group& GetGroup(std::string_view name);
    const Group& GetGroup(unsigned index);
    void NewGroup();
    void RemoveGroup(unsigned index);
    void RemoveAllGroups();

    nlohmann::json Serialize();
    void Deserialize(const nlohmann::json& data, std::vector<GameObject*>& objects);

private:
    std::map<std::string, sf::Texture*>& textures;
    ProfileManager& profileManager;
    SelectionManager& selectionManager;
    std::vector<Group*> groups;
    
    static unsigned newGroupID;

    char nameBuffer[32] = "";
};
