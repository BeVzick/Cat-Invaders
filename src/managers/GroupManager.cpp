#include "GroupManager.h"

#include "../utills/ClampWindows.h"
#include "../entities/units/Engineer.h"
#include "../entities/units/heroes/Captain.h"
#include <cstring>
#include <imgui.h>
#include <imgui-SFML.h>

Group::Group(std::string name, Hero *leader)
    : name(name), leader(leader)
{
    if (leader)
        leader->SetHasGroup(true);
}

Group::~Group()
{
}

std::string Group::GetName()
{
    return name;
}

Hero* const Group::GetLeader()
{
    return leader;
}

const std::set<Unit*>& Group::GetUnits()
{
    return units;
}

void Group::SetName(std::string name)
{
    this->name = name;
}

void Group::SetLeader(Hero *leader)
{
    leader->SetIsLeader(true);
    this->leader = leader;
}

void Group::RemoveLeader()
{
    leader->SetIsLeader(false);
    leader = nullptr;
}

void Group::AddToGroup(Unit* unit)
{
    unit->SetHasGroup(true);
    units.insert(unit);
}

void Group::RemoveFropGroup(Unit* unit)
{
    unit->SetHasGroup(false);
    units.erase(unit);
}

nlohmann::json Group::Serialize()
{
    nlohmann::json group = nlohmann::json::object();

    group["name"] = name;

    if (leader)
        group["leader_id"] = leader->GetID();

    nlohmann::json unitIDs = nlohmann::json::array();
    for (auto& unit : units)
        unitIDs.push_back(unit->GetID());
    group["units"] = unitIDs;

    return group;
}

void Group::Deserialize(const nlohmann::json &data)
{
}

unsigned GroupManager::newGroupID = 0;

GroupManager::GroupManager(std::map<std::string, sf::Texture*>& textures, SelectionManager& selection_manager, ProfileManager& profile_manager)
    : textures(textures), selectionManager(selection_manager), profileManager(profile_manager)
{
}

GroupManager::~GroupManager()
{
    for (auto* g : groups)
        delete g;
}

void GroupManager::UpdateUI()
{
    ImGui::Begin("Groups", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    ClampImGuiWindow();

    if (ImGui::SmallButton("New Group"))
        NewGroup();
    ImGui::SameLine();
    if (ImGui::SmallButton("Delete all"))
        RemoveAllGroups();

    int groupToDelete = -1;
    Unit* unitToRemove = nullptr;

    int i = 0;
    for (auto& group : groups)
    {
        bool removeLeader = false;

        if (ImGui::CollapsingHeader((group->GetName() + "###" + std::to_string(i)).c_str()))
        {
            if (ImGui::BeginDragDropTarget())
            {
                if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("UNIT_PTR"))
                {
                    Unit* draggedUnit = *(Unit**)payload->Data;
                    Hero* leader = dynamic_cast<Hero*>(draggedUnit);

                    if (!draggedUnit->GetHasGroup() && (!leader || leader && !leader->GetIsLeader()))
                    {
                        group->AddToGroup(draggedUnit);
                        draggedUnit->SetHasGroup(true);
                    }
                }

                ImGui::EndDragDropTarget();
            }

            Hero* leader = group->GetLeader();
            if (leader)
            {
                sf::Texture* texture;

                if (dynamic_cast<Captain*>(leader))
                    texture = textures["captain_icon"];

                if (ImGui::ImageButton(("Leader #" + std::to_string(i)).c_str(), *texture, {32, 32}))
                    ImGui::OpenPopup("LeaderContextMenu");

                if (ImGui::BeginPopup("LeaderContextMenu", ImGuiWindowFlags_NoMove))
                {
                    if (ImGui::Selectable("Profile"))
                        profileManager.SetObject(leader);
                    if (ImGui::Selectable("Remove"))
                        removeLeader = true;

                    ImGui::EndPopup();
                }
            }
            else
            {
                ImVec2 size = ImVec2(32 + ImGui::GetStyle().FramePadding.x * 2, 32 + ImGui::GetStyle().FramePadding.y * 2);
                ImGui::Button(("##Leader" + std::to_string(i)).c_str(), size);
            }

            if (ImGui::BeginDragDropTarget())
            {
                if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("UNIT_PTR"))
                {
                    Unit* draggedUnit = *(Unit**)payload->Data;
                    Hero* leader = dynamic_cast<Hero*>(draggedUnit);

                    if (leader && !leader->GetIsLeader())
                    {
                        group->SetLeader(leader);
                        if (leader->GetHasGroup())
                        {
                            unitToRemove = draggedUnit;
                            leader->SetHasGroup(false);
                        }
                        leader->SetIsLeader(true);
                    }
                }

                ImGui::EndDragDropTarget();
            }

            ImGui::SameLine();
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + ((32 + ImGui::GetStyle().FramePadding.y * 2) - ImGui::GetTextLineHeight()) / 2);
            ImGui::Text("Leader");

            ImGui::Separator();

            ImGui::BeginChild(("Units##" + std::to_string(i)).c_str(), {0 ,0}, ImGuiChildFlags_AutoResizeY);

            int j = 0;
            for (auto& unit : group->GetUnits())
            {
                sf::Texture* texture;
                if (dynamic_cast<Engineer*>(unit))
                    texture = textures["engineer_icon"];
                else if (dynamic_cast<Captain*>(unit))
                    texture = textures["captain_icon"];

                if (j > 0)
                    ImGui::SameLine();
                if (ImGui::ImageButton(("Unit #" + std::to_string(j)).c_str(), *texture, {32, 32}))
                    ImGui::OpenPopup(("UnitContextMenu##" + std::to_string(j)).c_str());
                
                if (ImGui::BeginPopup(("UnitContextMenu##" + std::to_string(j)).c_str(), ImGuiWindowFlags_NoMove))
                {
                    if (ImGui::Selectable("Profile"))
                        profileManager.SetObject(unit);
                    if (ImGui::Selectable("Remove"))
                        unitToRemove = unit;

                    ImGui::EndPopup();
                }

                ++j;
            }

            ImGui::EndChild();

            if (ImGui::BeginDragDropTarget())
            {
                if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("UNIT_PTR"))
                {
                    Unit* draggedUnit = *(Unit**)payload->Data;
                    Hero* leader = dynamic_cast<Hero*>(draggedUnit);

                    if (!draggedUnit->GetHasGroup() && (!leader || leader && !leader->GetIsLeader()))
                    {
                        group->AddToGroup(draggedUnit);
                        draggedUnit->SetHasGroup(true);
                    }
                }

                ImGui::EndDragDropTarget();
            }

            ImGui::Separator();
            ImGui::Spacing();

            if (ImGui::SmallButton(("Select##" + std::to_string(i)).c_str()))
            {
                selectionManager.ClearSelect();
                for (auto& unit : group->GetUnits())
                    selectionManager.AddSelect(unit);
                if (leader)
                    selectionManager.AddSelect(leader);
            }

            ImGui::SameLine();
            if (ImGui::SmallButton(("Edit##" + std::to_string(i)).c_str()))
            {
                std::strncpy(nameBuffer, group->GetName().c_str(), sizeof(nameBuffer));
                nameBuffer[sizeof(nameBuffer) - 1] = '\0';
                ImGui::OpenPopup(("Edit Group##" + std::to_string(i)).c_str());
            }
                
            ImGui::SameLine();
            if (ImGui::SmallButton(("Delete##" + std::to_string(i)).c_str()))
                groupToDelete = i;

            ImGui::Spacing();
        }

        ImGui::SetNextWindowPos(ImGui::GetMainViewport()->GetCenter(), 0, {0.5f, 0.5f});
        if (ImGui::BeginPopupModal(("Edit Group##" + std::to_string(i)).c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize))
        {
            ImGui::InputText("Name", nameBuffer, sizeof(nameBuffer));

            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Spacing();

            if (ImGui::Button("Save"))
            {
                group->SetName(nameBuffer);
                ImGui::CloseCurrentPopup();
            }
            ImGui::SameLine();
            if (ImGui::Button("Cancel"))
                ImGui::CloseCurrentPopup();

            ImGui::EndPopup();
        }

        if (removeLeader)
            group->RemoveLeader();

        if (unitToRemove)
            group->RemoveFropGroup(unitToRemove);

        ++i;
    }

    if (groupToDelete != -1)
        RemoveGroup(groupToDelete);

    ImGui::End();
}

unsigned GroupManager::GetNewGroupID()
{
    return newGroupID;
}

void GroupManager::SetNewGroupID(unsigned id)
{
    newGroupID = id;
}

const Group& GroupManager::GetGroup(std::string_view name)
{
    for (auto* g : groups)
        if (g->GetName() == name)
            return *g;
}

const Group &GroupManager::GetGroup(unsigned index)
{
    return *groups[index];
}

void GroupManager::NewGroup()
{
    unsigned len = groups.size();

    groups.push_back(new Group("Group #" + std::to_string(newGroupID++)));
}

void GroupManager::RemoveGroup(unsigned index)
{
    Group* group = groups[index];

    if (group->GetLeader())
        group->RemoveLeader();

    for (auto& unit : group->GetUnits())
        unit->SetHasGroup(false);

    delete group;
    groups.erase(groups.begin() + index);
}

void GroupManager::RemoveAllGroups()
{
    for (auto& group : groups)
    {
        if (group->GetLeader())
            group->RemoveLeader();

        for (auto& unit : group->GetUnits())
            unit->SetHasGroup(false);
        
        delete group;
    }
    groups.clear();
}

nlohmann::json GroupManager::Serialize()
{
    nlohmann::json groupsJson = nlohmann::json::array();

    for (auto& group : groups)
        groupsJson.push_back(group->Serialize());

    return groupsJson;
}

void GroupManager::Deserialize(const nlohmann::json &data)
{
}

void GroupManager::Deserialize(const nlohmann::json& data, std::vector<GameObject*>& objects)
{
    for (auto* g : groups)
        delete g;
    groups.clear();

    for (const auto& groupJson : data)
    {
        Group* group = new Group(groupJson.value("name", ""));
        
        if (groupJson.contains("leader_id"))
        {
            long id = groupJson.value("leader_id", -1);

            for (auto& obj : objects)
            {
                Hero* leader = dynamic_cast<Hero*>(obj);
            
                if (leader && leader->GetID() == id)
                {
                    leader->SetIsLeader(false);
                    group->SetLeader(leader);
                }
            }
        }

        for (const long id : groupJson["units"])
        {
            for (auto& obj : objects)
            {
                Unit* unit = dynamic_cast<Unit*>(obj);
            
                if (unit && unit->GetID() == id)
                    group->AddToGroup(unit);
            }
        }

        groups.push_back(group);
    }
}
