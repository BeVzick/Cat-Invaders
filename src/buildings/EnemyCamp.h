#pragma once

#include "../entities/enemies/Enemy.h"
#include "../ISerializable.h"
#include <vector>
#include <SFML/Graphics/CircleShape.hpp>

class EnemyAICoordinator;

struct WaveEntry
{
    EnemyType type;
    unsigned count;
};

class AggroEllipse
{
public:
    AggroEllipse(float radius_x, float radius_y, unsigned point_count = 60);

    void SetPosition(sf::Vector2f pos);
    void Render(sf::RenderTarget& target);

private:
    sf::VertexArray fill;
    sf::VertexArray outline;
    float rx;
    float ry;
    sf::Vector2f center;
    unsigned pointCount;

    void Rebuild();
};

class EnemyCamp : public GameObject, public ISerializable
{
public:
    EnemyCamp(sf::Texture& texture, std::vector<GameObject *>& worldObjects, std::map<std::string, sf::Texture *>& textures);
    EnemyCamp(sf::Texture& texture, sf::Vector2f pos, float spawn_interval, float aggro_radius, unsigned max_enemies,
        std::vector<GameObject *>& worldObjects, std::map<std::string, sf::Texture *>& textures);
    ~EnemyCamp();

    void UpdateAnimations(float dt) override {}
    void Update(sf::Vector2f mouse_pos_view, float dt) override;
    void Render(sf::RenderTarget& target) override;
    void ShowData() override;

    void AddWaveEntry(EnemyType type, unsigned count);
    void TakeDamage(unsigned damage);
    bool IsDestriyed() const;

    void CheckAggro(const std::vector<GameObject*>& objects, const std::vector<GameObject*>& worldObjects);
    float GetAggroRadius() const;

    const std::vector<Enemy*>& GetSpawnedEnemies();
    void SetPlayerBasePos(sf::Vector2f pos);
    void SetAssaultInterval(float seconds);

    nlohmann::json Serialize() override;
    void Deserialize(const nlohmann::json& data) override;

protected:
    std::string GetType() const override;

private:
    EnemyAICoordinator* aiCoordinator = nullptr;
    sf::Vector2f playerBasePos;
    std::vector<GameObject *>& worldObjects;
    std::map<std::string, sf::Texture *>& textures;
    std::vector<WaveEntry> waveEntries;
    std::vector<Enemy*> spawnedEnemies;
    float spawnInterval;
    float spawnTimer;
    float aggroRadius;
    unsigned maxEnemies;
    bool aggroed;
    bool destroyed;
    AggroEllipse aggroShape;

    void SpawnWave();
};
