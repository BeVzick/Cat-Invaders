#include "ProfileManager.h"

#include "../utills/ClampWindows.h"
#include <imgui.h>
#include <imgui-SFML.h>

ProfileManager::ProfileManager(GameObject *object)
    : object(object), isOpen(false)
{
}

ProfileManager::~ProfileManager()
{
}

void ProfileManager::Show()
{
    if (object != nullptr && isOpen)
    {
        ImGui::Begin("Profile", &isOpen, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse);
        ClampImGuiWindow();

        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 128) / 2);
        ImGui::Image(object->sprite, {128, 128});
        ImGui::Separator();

        object->ShowData();

        ImGui::End();
    }
}

void ProfileManager::SetObject(GameObject* object)
{
    this->object = object;
    isOpen = true;
}
