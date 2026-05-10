#include "SelectionManager.h"

#include "../entities/units/Engineer.h"
#include "../entities/units/heroes/Captain.h"
#include <algorithm>
#include <imgui.h>
#include <imgui-SFML.h>

SelectionManager::SelectionManager(std::map<std::string, sf::Texture*>& textures, ProfileManager& profile_manager)
    : textures(textures), profileManager(profile_manager)
{
}

SelectionManager::~SelectionManager()
{
}

void SelectionManager::UpdateUI()
{
    ImGui::Begin("Selected Units");

    float width = ImGui::GetContentRegionAvail().x;

    ImGui::BeginChild("Units", {width * 0.65f, 0});
    Unit* unitToRemove = nullptr;

    int i = 0;
    for (auto& unit : selectedUnits)
    {
        if (i > 0)
            ImGui::SameLine();

        sf::Texture* texture;
        if (dynamic_cast<Engineer*>(unit))
            texture = textures["engineer_icon"];
        else if (dynamic_cast<Captain*>(unit))
            texture = textures["captain_icon"];

        if (ImGui::ImageButton(("Unit #" + std::to_string(i)).c_str(), *texture, sf::Vector2f(32, 32)))
            ImGui::OpenPopup(("UnitContextMenu##" + std::to_string(i)).c_str());

        if (ImGui::BeginPopup(("UnitContextMenu##" + std::to_string(i)).c_str(), ImGuiWindowFlags_NoMove))
        {
            if (ImGui::Selectable("Profile"))
                profileManager.SetObject(unit);
            if (ImGui::Selectable("Remove"))
                unitToRemove = unit;

            ImGui::EndPopup();
        }

        if (ImGui::BeginDragDropSource())
        {
            Unit* currUnit = unit;
            ImGui::SetDragDropPayload("UNIT_PTR", &currUnit, sizeof(Unit*));

            ImGui::Image(*texture, {24, 24});

            ImGui::EndDragDropSource();
        }

        ++i;
    }

    if (unitToRemove)
        ClearSelected(unitToRemove);

    ImGui::EndChild();

    ImGui::SameLine();

    ImGui::BeginChild("Actions", {width * 0.35, 0});

    ImGui::SeparatorText("Actions");

    ImGui::EndChild();

    ImGui::End();
}

void SelectionManager::SetSelect(Unit* object)
{
    ClearSelect();
    selectedUnits.insert(object);
    object->SetIsSelected(true);
}

void SelectionManager::SetSelect(Building* object)
{
}

void SelectionManager::SetSelect(std::vector<Unit*> objects)
{
}

void SelectionManager::AddSelect(Unit* object)
{
    object->SetIsSelected(true);
    selectedUnits.insert(object);
}

void SelectionManager::ClearSelected(Unit* object)
{
    object->SetIsSelected(false);
    selectedUnits.erase(object);
}

void SelectionManager::ClearSelected(Building *object)
{
}

void SelectionManager::ClearSelect()
{
    for (auto& unit : selectedUnits)
        unit->SetIsSelected(false);
    selectedUnits.clear();
}

void SelectionManager::IssueCommand(IAction *command)
{
}

std::set<Unit *>& SelectionManager::GetSelected()
{
    return selectedUnits;
}
