#pragma once

#include "State.h"
#include "../managers/Managers.h"
#include "../entities/units/Unit.h"
#include "../tilemap/TileMap.h"
#include "../SelectRect.h"
#include <string>
#include <map>
#include <imgui.h>

class GameState : public State
{
public:
    GameState(sf::RenderWindow& window, std::vector<State*>& states, Settings& settings);
    virtual ~GameState();

    void UpdateViewport();
    void Update(float dt) override;
    void Render() override;

    void OnResize() override;

private:
    ResourceManager* resourceManager;
    ResearchManager* researchManager;
    EnemyManager* enemyManager;
    GroupManager* groupManager;
    SelectionManager* selectionManager;
    ProfileManager* profileManager;

    SelectRect selectRect;

    sf::View view;

    std::map<std::string, sf::Texture*> textures;
    TileMap* tilemap;
    std::vector<GameObject*> objects;

    bool isPaused;

    ImGuiWindowFlags pauseFlags;

    // Debug
    sf::Font font;
    sf::Text fpsText;
    float fpsTimer;
};
