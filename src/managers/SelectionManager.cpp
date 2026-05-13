#include "SelectionManager.h"

#include "../utills/ClampWindows.h"
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

void SelectionManager::UpdateUI(Pointer& pointer)
{
    if (selectedUnits.empty() && pointer.GetState() != PointerState::None)
        pointer.SetState(PointerState::None);

    ImGui::Begin("Selected Units");
    ClampImGuiWindow();

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
    ImGui::BeginChild("Actions", {width * 0.45f, 96});
    if (!selectedUnits.empty())
        RenderActionBar(pointer);
    ImGui::EndChild();

    if (selectedUnits.size() == 1)
    {
        Hero* hero = dynamic_cast<Hero*>(*selectedUnits.begin());
        if (hero && !hero->GetSkills().empty())
        {
            ImGui::Separator();
            ImGui::BeginChild("Skills", {0, 56}, ImGuiChildFlags_AutoResizeY);
            RenderSkillBar();
            ImGui::EndChild();
        }
    }

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

void SelectionManager::RenderActionBar(Pointer& pointer)
{
    PointerState pointer_state = pointer.GetState();
    auto modeBtn = [&](const char* label, PointerState state, const char* tooltip) {
        bool active = (pointer_state == state);
        if (active)
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.7f, 0.3f, 1.f));
        if (ImGui::Button(label, {52, 40}))
            pointer.SetState((pointer_state == state) ? PointerState::None : state);
        if (active)
            ImGui::PopStyleColor();
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("%s", tooltip);
    };

    ImGui::SeparatorText("Actions");
    modeBtn("Move", PointerState::Move, "Right-click to move (M)");
    ImGui::SameLine();
    modeBtn("Attack", PointerState::Attack, "Right-click to attack (A)");
    ImGui::SameLine();
    modeBtn("Defend", PointerState::Defend, "Right-click to defend position (D)");

    bool hasEngineer = std::any_of(selectedUnits.begin(), selectedUnits.end(),
        [](Unit* u) { return dynamic_cast<Engineer*>(u) != nullptr; }
    );
    if (hasEngineer)
    {
        // modeBtn("Gather", PointerState::Gather, "Right-click resource node to gather");
        // ImGui::SameLine();
        modeBtn("Build", PointerState::Build, "Open build menu (B)");
    }
}

void SelectionManager::RenderSkillBar()
{
    if (selectedUnits.size() != 1)
        return;
    Hero* hero = dynamic_cast<Hero*>(*selectedUnits.begin());
    if (!hero)
        return;

    ImGui::SeparatorText("Skills");
    int idx = 0;
    for (auto* skill : hero->GetSkills())
    {
        if (idx > 0)
            ImGui::SameLine();

        bool ready = skill->IsReady();
        if (!ready)
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.4f, 0.4f, 0.4f, 1.f));

        if (ImGui::Button(skill->GetName().c_str(), {70, 36}) && ready)
            hero->ActivateSkill(static_cast<unsigned>(idx));
        
        if (!ready)
        {
            float progress = skill->GetCooldownProgress();
            ImVec2 btn = ImGui::GetItemRectMin();
            ImVec2 btnMax = ImGui::GetItemRectMax();
            float fill = btn.x + (btnMax.x - btn.x) * progress;
            ImGui::GetWindowDrawList()->AddRectFilled(
                {btn.x, btnMax.y - 4}, {fill, btnMax.y},
                IM_COL32(80, 200, 120, 200));
            ImGui::PopStyleColor();

            if (ImGui::IsItemHovered())
                ImGui::SetTooltip("%s\b%s", skill->GetName().c_str(), skill->GetDescription().c_str());
            
            ++idx;
        }
    }
}
