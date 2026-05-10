#pragma once

#include "ProfileManager.h"
#include "../entities/units/Unit.h"
#include "../buildings/Building.h"
#include "../actions/IAction.h"
#include <vector>
#include <set>

enum class CursorMode
{
    Normal,
    Move,
    Attack,
    Defend,
    Build,
    Gather
};

class SelectionManager
{
public:
    SelectionManager(std::map<std::string, sf::Texture*>& textures, ProfileManager& profile_manager);
    ~SelectionManager();

    void UpdateUI(CursorMode& cursor_mode);

    void SetSelect(Unit* object);
    void SetSelect(Building* object);
    void SetSelect(std::vector<Unit*> objects);
    void AddSelect(Unit* object);
    void ClearSelected(Unit* object);
    void ClearSelected(Building* object);
    void ClearSelect();
    void IssueCommand(IAction* command);

    std::set<Unit*>& GetSelected();

private:
    ProfileManager& profileManager;
    std::map<std::string, sf::Texture*>& textures;
    std::set<Unit*> selectedUnits;
    Building* selectedBuilding;

    void RenderActionBar(CursorMode& cursor_mode);
    void RenderSkillBar();
};
