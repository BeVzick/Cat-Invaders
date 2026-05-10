#include "ResearchManager.h"

#include "../researches/IronPawResearch.h"
#include <algorithm>
#include <imgui.h>

ResearchManager::ResearchManager()
{
}

ResearchManager::~ResearchManager()
{
    while (!queue.empty())
    {
        delete queue.front();
        queue.pop();
    }
    for (auto* r : available)
        delete r;
}

void ResearchManager::Update(float dt, std::vector<GameObject *>& objects)
{
    if (paused || queue.empty())
        return;

    Research* current = queue.front();
    if (current->Tick(dt))
    {
        completed.push_back(current->GetName());
        current->GetEffect().Apply(objects);
        delete current;
        queue.pop();
    }
}

void ResearchManager::UpdateUI()
{
    ImGui::Begin("Research", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

    if (!queue.empty())
    {
        Research* current = queue.front();
        ImGui::SeparatorText("In Progress");
        ImGui::Text("%s", current->GetName().c_str());

        float progress = current->GetProgress();
        char buffer[32];
        std::snprintf(buffer, sizeof(buffer), "%.0f%%", progress * 100.f);
        ImGui::ProgressBar(progress, {-1.f, 0.f}, buffer);

        if (!paused && ImGui::SmallButton("Pause"))
            Pause();
        if (paused && ImGui::SmallButton("Resume"))
            Unpause();
        ImGui::SameLine();
        if (ImGui::SmallButton("Cancel"))
            CancelCurrent();

        ImGui::Spacing();
    }
    else
        ImGui::TextDisabled("No active research");

    if (queue.size() > 1)
    {
        ImGui::SeparatorText("Queue");
        std::queue<Research*> temp = queue;
        temp.pop();
        int i = 1;
        while (!temp.empty())
        {
            ImGui::BulletText("%d. %s", i++, temp.front()->GetName().c_str());
            temp.pop();
        }
        ImGui::Spacing();
    }

    ImGui::SeparatorText("Available");
    for (auto* r : available)
    {
        bool alreadyDone = std::find(completed.begin(), completed.end(), r->GetName()) != completed.end();
        if (alreadyDone)
        {
            ImGui::TextDisabled("[Done] %s", r->GetName().c_str());
            continue;
        }

        if (ImGui::Button(r->GetName().c_str()))
        {
            if (r->GetName() == "Iron Paw")
                Enqueue(new IronPawResearch(100.f));
        }
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("%s\nTime: %us", r->GetEffect().description.c_str(), r->GetResearchTime());
    }

    if (!completed.empty())
    {
        ImGui::SeparatorText("Completed");
        for (auto& name : completed)
            ImGui::TextColored({0.4f, 0.9f, 0.4f, 1.f}, "[+] %s", name.c_str());
    }

    ImGui::End();
}

bool ResearchManager::IsPaused() const
{
    return paused;
}

void ResearchManager::Pause()
{
    paused = true;
}

void ResearchManager::Unpause()
{
    paused = false;
}

void ResearchManager::Enqueue(Research *research)
{
    queue.push(research);
}

void ResearchManager::CancelCurrent()
{
    if (!queue.empty())
    {
        delete queue.front();
        queue.pop();
    }
}

void ResearchManager::ClearQueue()
{
    while (!queue.empty())
    {
        delete queue.front();
        queue.pop();
    }
}

void ResearchManager::AddAvailable(Research* research)
{
    available.push_back(research);
}

const Research* ResearchManager::GetCurrent() const
{
    return queue.empty() ? nullptr : queue.front();
}

bool ResearchManager::HasPending() const
{
    return !queue.empty();
}

const std::vector<std::string> &ResearchManager::GetCompleted() const
{
    return completed;
}
