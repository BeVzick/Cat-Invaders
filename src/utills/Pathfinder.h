#pragma once

#include <vector>
#include <functional>
#include <SFML/System/Vector2.hpp>

enum class EnemyAIState { Wander, Chase, Attack, Rally, Assault };

struct AStarNode
{
    sf::Vector2i cell;
    float g;
    float h;
    AStarNode* parent = nullptr;

    float f() const { return g + h; }
};

class Pathfinder
{
public:
    static std::vector<sf::Vector2f> FindPath(sf::Vector2f start, sf::Vector2f goal, sf::Vector2f grid_size, std::function<bool(sf::Vector2i)> is_walkable);

private:
    static sf::Vector2i WorldToCell(sf::Vector2f pos, sf::Vector2f grid_size);
    static sf::Vector2f CellToWorld(sf::Vector2i cell, sf::Vector2f grid_size);
    static float Heuristic(sf::Vector2i a, sf::Vector2i b);
    static std::vector<sf::Vector2i> Neighbours(sf::Vector2i cell);
};
