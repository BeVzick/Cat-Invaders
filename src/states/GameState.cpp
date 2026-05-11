#include "GameState.h"

#include "SettingsState.h"
#include "../entities/units/heroes/Captain.h"
#include "../entities/units/Engineer.h"
#include "../entities/enemies/Bat.h"
#include "../utills/CoordinatesConverter.h"
#include "../actions/MoveToAction.h"
#include "../utills/CameraBounds.h"
#include <random>
#include <imgui.h>

GameState::GameState(sf::RenderWindow& window, std::vector<State *>& states, Settings& settings)
    : State(window, states, settings), /* Debug */ font("/usr/share/fonts/TTF/Hack-Regular.ttf"), fpsText(font), fpsTimer(0.f), isPaused(false)
{
    pauseFlags = ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove;

    LoadTextures();

    tilemap = new TileMap({50, 50, 1});
    for (int i = 0; i < 50; ++i)
        for (int j = 0; j < 50; ++j)
        {
            // int r = std::rand() % 2;

            tilemap->SetTile({i, j, 0}, new Tile(*textures["grass"],
                sf::IntRect({0, 0}, {32, 32}),
                CoordinatesCovnverter::WorldToIso({i, j}, {32, 32})
            ));
        }
    CameraBounds::SetMapSize({50, 50}, {32, 16});

    resourceManager = new ResourceManager();
    researchManager = new ResearchManager();
    enemyManager = new EnemyManager();
    profileManager = new ProfileManager();
    selectionManager = new SelectionManager(textures, *profileManager);
    groupManager = new GroupManager(textures, *selectionManager, *profileManager);
    
    Captain* c = new Captain(*textures["captain"]);
    c->SetPos({50, 100});
    objects.push_back(c);

    objects.push_back(new Engineer(*textures["engineer"]));
    Engineer* e = new Engineer(*textures["engineer"]);
    e->SetPos({100, 50});
    objects.push_back(e);

    EnemyCamp* camp = new EnemyCamp(*textures["tile"], {400, 300}, 30.f, 180.f, 4);
    camp->AddWaveEntry(EnemyType::Bat, 2);
    enemyCamps.push_back(camp);

    objects.push_back(new Bat(*textures["bat"]));

    fpsText.setCharacterSize(18);
    fpsText.setPosition({10.f, 10.f});

    UpdateViewport();
}

GameState::~GameState()
{
    delete resourceManager;
    delete researchManager;
    delete enemyManager;
    delete groupManager;
    delete selectionManager;
    delete profileManager;

    delete tilemap;

    for (auto* obj : objects)
        delete obj;

    for (auto& tex : textures)
        delete tex.second;
}

void GameState::UpdateViewport()
{
    const sf::Vector2f targetSize = {1920, 1080};
    const float targetRatio = targetSize.x / targetSize.y;

    sf::Vector2f windowSize = sf::Vector2f(window.getSize());
    float windowRatio = windowSize.x / windowSize.y;

    sf::Vector2f viewportSize = {1.f, 1.f};
    sf::Vector2f viewportPos = {};

    if (windowRatio > targetRatio) {
        viewportSize.x = targetRatio / windowRatio;
        viewportPos.x = (1.f - viewportSize.x) / 2.f;
    }
    else
    {
        viewportSize.y = windowRatio / targetRatio;
        viewportPos.y = (1.f - viewportSize.y) / 2.f;
    }

    view.setSize({1920, 1080});
    view.setCenter({});
    view.setViewport(sf::FloatRect(viewportPos, viewportSize));

    view.zoom(0.3f);
}

void GameState::Update(float dt)
{
    tilemap->Update();

    for (auto* obj : objects)
    {
        obj->Update(mousePosView, dt);
        if (!isPaused)
            obj->UpdateAnimations(dt);
    }

    for (auto* camp : enemyCamps)
    {
        camp->Update({}, dt);
        camp->CheckAggro(objects, objects);
    }

    if (ImGui::IsKeyReleased(ImGuiKey_Escape))
        isPaused = !isPaused;    
    
    if (isPaused)
        RenderPauseMenu();
    else
    {
        resourceManager->UpdateUI();
        researchManager->UpdateUI();
        selectionManager->UpdateUI(cursorMode);
        groupManager->UpdateUI();
        profileManager->Show();

        bool isMouseOverUI = ImGui::GetIO().WantCaptureMouse;

        if (!isMouseOverUI)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || mousePosView.y >= 0.f && mousePosView.y <= 20.f)
                view.move(sf::Vector2f(0.f, -500.f) * dt);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || mousePosView.y <= window.getSize().y && mousePosView.y >= window.getSize().y - 20.f)
                view.move(sf::Vector2f(0.f, 500.f) * dt);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || mousePosView.x >= 0.f && mousePosView.x <= 20.f)
                view.move(sf::Vector2f(-500.f, 0.f) * dt);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || mousePosView.x <= window.getSize().x && mousePosView.x >= window.getSize().x - 20.f)
                view.move(sf::Vector2f(500.f, 0.f) * dt);

            CameraBounds::Clamp(view);

            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
            {
                sf::Vector2f targetPos = window.mapPixelToCoords(sf::Mouse::getPosition(window), view);
                bool isShiftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift);

                for (auto& unit : selectionManager->GetSelected())
                    unit->IssueCommand(new MoveToAction(targetPos), isShiftPressed);
            }
        }

        sf::Vector2f mousePosView = window.mapPixelToCoords(mousePosWindow, view);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !isMouseOverUI)
        {
            if (!selectRect.GetStartedSelection())
            {
                selectRect.SetSelectionStart(mousePosView);
                selectRect.SetStartedSelection(true);
            }
            else
                selectRect.UpdateRect(selectRect.GetSelectionStart(), mousePosView);
        }
        else if (ImGui::IsKeyReleased(ImGuiKey_MouseLeft) && !isMouseOverUI)
        {
            selectRect.SelectUnits(window, view, *selectionManager, objects);
            selectRect.Reset();
        }
    }

    if (fpsTimer >= 0.25f)
    {
        fpsText.setString("FPS: " + std::to_string(static_cast<int>((dt > 0.f) ? 1.f / dt : 0.f)));
        fpsTimer = 0.f;
    }
    fpsTimer += dt;
}

void GameState::Render()
{
    window.setView(view);
    tilemap->Render(window);

    for (auto* obj : objects)
        obj->Render(window);

    for (auto* camp : enemyCamps)
        camp->Render(window);


    if (selectRect.GetStartedSelection())
        selectRect.Render(window);

    // Debug
    window.setView(window.getDefaultView());
    if (settings.showFPS)
        window.draw(fpsText);
}

void GameState::OnResize()
{
    UpdateViewport();
}

void GameState::LoadTextures()
{
    auto load = [&](const std::string& key, const std::string& path) {
        textures[key] = new sf::Texture(path);
    };
    load("tile", "res/tiles/test_tile.png");
    load("grass", "res/tiles/grass.png");
    
    load("engineer_icon", "res/icons/engineer_icon.png");
    load("captain_icon", "res/icons/captain_icon.png");

    load("engineer", "res/sprites/units/engineer.png");
    load("captain", "res/sprites/units/heroes/captain.png");

    load("bat", "res/sprites/enemies/bat.png");
}

void GameState::RenderPauseMenu()
{
    ImGui::SetNextWindowPos({ImGui::GetIO().DisplaySize.x * 0.5, ImGui::GetIO().DisplaySize.y * 0.5}, 0, {0.5f, 0.5f});
        ImGui::SetNextWindowSize({ImGui::GetIO().DisplaySize.x * 0.3, ImGui::GetIO().DisplaySize.y * 0.6});

        ImGui::Begin("Pause", nullptr, pauseFlags);

        if (ImGui::BeginTable("PauseTable", 3))
        {
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::TableNextColumn();

            ImGui::SetWindowFontScale(3);
            ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("PAUSE").x) / 2);
            ImGui::Text("PAUSE", ImGui::GetFontSize(), 24);
            ImGui::SetWindowFontScale(1);

            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::TableNextColumn();

            ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 250) / 2);
            if (ImGui::Button("Resume", {250, 50}))
                isPaused = false;

            ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 250) / 2);
            if (ImGui::Button("Save", {250, 50}))
                isPaused = false;

            ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 250) / 2);
            if (ImGui::Button("Settings", {250, 50}))
                PushState(new SettingsState(window, states, settings));
            
            ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 250) / 2);
            if (ImGui::Button("Save & quit", {250, 50}))
                quit = true;

            ImGui::TableNextColumn();

            ImGui::EndTable();
        }

        ImGui::End();
}
