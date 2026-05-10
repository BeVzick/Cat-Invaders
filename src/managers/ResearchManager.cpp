#include "ResearchManager.h"

#include <imgui.h>

ResearchManager::ResearchManager()
{
}

ResearchManager::~ResearchManager()
{
}

void ResearchManager::UpdateUI()
{
    ImGui::Begin("Research");

    ImGui::End();
}

bool ResearchManager::IsPaused()
{
    return paused;
}

void ResearchManager::StartResearch()
{
}

void ResearchManager::StopResearch()
{
}

void ResearchManager::AddResearch(Research *research)
{
}

void ResearchManager::RemoveResearch()
{
}
