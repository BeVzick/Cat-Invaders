#pragma once

#include "entities/enemies/Enemy.h"
#include <vector>
#include <SFML/Graphics/CircleShape.hpp>

struct WaveEntry
{
    EnemyType type;
    unsigned count;
};

class EnemyCamp : public GameObject
{
public:
    EnemyCamp(sf::Texture& texture, sf::Vector2f pos, float spawn_interval, float aggro_radius, unsigned max_enemies);
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

private:
    std::vector<WaveEntry> waveEntries;
    std::vector<Enemy*> spawnedEnemies;
    float spawnInterval;
    float spawnTimer;
    float aggroRadius;
    unsigned maxEnemies;
    bool aggroed;
    bool destroyed;
    sf::CircleShape aggroCircle;

    void SpawnWave(const std::vector<GameObject*>& worldObjects, std::map<std::string, sf::Texture*>& textures);
};
