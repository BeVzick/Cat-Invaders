#include "ClampWindows.h"

#include <imgui.h>

void ClampImGuiWindow()
{
    ImVec2 pos = ImGui::GetWindowPos();
    ImVec2 size = ImGui::GetWindowSize();
    ImVec2 screen = ImGui::GetIO().DisplaySize;

    bool moved = false;

    if (pos.x < 0)
    {
        pos.x = 0;
        moved = true;
    }
    if (pos.x + size.x > screen.x)
    {
        pos.x = screen.x - size.x;
        moved = true;
    }

    if (pos.y < 0)
    {
        pos.y = 0;
        moved = true;
    }
    if (pos.y + size.y > screen.y)
    {
        pos.y = screen.y - size.y;
        moved = true;
    }

    if (moved)
        ImGui::SetWindowPos(pos);
}