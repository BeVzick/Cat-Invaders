#pragma once

#include "State.h"
#include "../buildings/EnemyCamp.h"
#include "../managers/Managers.h"
#include "../entities/units/Unit.h"
#include "../tilemap/TileMap.h"
#include "../SelectRect.h"
#include "../Pointer.h"
#include <string>
#include <map>
#include <imgui.h>

class GameState : public State, public ISerializable
{
public:
    GameState(sf::RenderWindow& window, std::vector<State*>& states, Settings& settings);
    virtual ~GameState();

    void UpdateViewport();
    void Update(float dt) override;
    void Render() override;

    void LoadLastGame();

    void OnResize() override;
    
    nlohmann::json Serialize() override;
    void Deserialize(const nlohmann::json& data) override;

private:
    ResourceManager* resourceManager;
    ResearchManager* researchManager;
    EnemyManager* enemyManager;
    GroupManager* groupManager;
    SelectionManager* selectionManager;
    ProfileManager* profileManager;
    SaveManager* saveManager;

    SelectRect selectRect;

    sf::View view;

    std::map<std::string, sf::Texture*> textures;
    TileMap* tilemap;
    std::vector<GameObject*> objects;
    std::vector<EnemyCamp*> enemyCamps;
    GameObject* selectedEnemy = nullptr;

    Pointer* pointer;

    bool isPaused;
    bool isSaving;
    ImGuiWindowFlags windowFlags;

    // Debug
    sf::Font font;
    sf::Text fpsText;
    float fpsTimer;

    void LoadTextures();
    void RenderPauseMenu();
    void RenderSavesManu();
};
