#include "Pathfinder.h"

#include <queue>
#include <algorithm>

namespace
{
    struct Vec2iHash
    {
        std::size_t operator()(sf::Vector2i v) const
        {
            return std::hash<long long>{}(((long long)v.x << 32) | (unsigned)v.y);
        }
    };
}

std::vector<sf::Vector2f> Pathfinder::FindPath(sf::Vector2f start, sf::Vector2f goal, sf::Vector2f grid_size, std::function<bool(sf::Vector2i)> is_walkable)
{
    sf::Vector2i startCell = WorldToCell(start, grid_size);
    sf::Vector2i goalCell = WorldToCell(goal, grid_size);

    if (startCell == goalCell)
        return { goal };

    auto cmp = [](AStarNode* a, AStarNode* b){ return a->f() > b->f(); };
    std::priority_queue<AStarNode*, std::vector<AStarNode*>, decltype(cmp)> open(cmp);

        std::unordered_map<sf::Vector2i, AStarNode*, Vec2iHash> allNodes;
    std::unordered_map<sf::Vector2i, float, Vec2iHash>      bestG;
 
    auto makeNode = [&](sf::Vector2i cell, float g, float h, AStarNode* parent) -> AStarNode*
    {
        auto* node = new AStarNode{ cell, g, h, parent };
        allNodes[cell] = node;
        return node;
    };
 
    open.push(makeNode(startCell, 0.f, Heuristic(startCell, goalCell), nullptr));
    bestG[startCell] = 0.f;
 
    static constexpr int kMaxIterations = 2048; // захист від зависання
    int iterations = 0;
    AStarNode* found = nullptr;
 
    while (!open.empty() && iterations++ < kMaxIterations)
    {
        AStarNode* current = open.top(); open.pop();
 
        if (current->cell == goalCell)
        {
            found = current;
            break;
        }
 
        for (sf::Vector2i nb : Neighbours(current->cell))
        {
            if (!is_walkable(nb))
                continue;
 
            bool isDiag = (nb.x != current->cell.x && nb.y != current->cell.y);
            float moveCost = isDiag ? 1.414f : 1.f;
            float newG = current->g + moveCost;
 
            auto it = bestG.find(nb);
            if (it != bestG.end() && newG >= it->second)
                continue;
 
            bestG[nb] = newG;
            open.push(makeNode(nb, newG, Heuristic(nb, goalCell), current));
        }
    }
 
    std::vector<sf::Vector2f> result;
    if (found)
    {
        for (AStarNode* n = found; n != nullptr; n = n->parent)
            result.push_back(CellToWorld(n->cell, grid_size));
        std::reverse(result.begin(), result.end());
        result.back() = goal; // точна кінцева позиція
    }
    else
        result.push_back(goal);
 
    for (auto& [cell, node] : allNodes)
        delete node;
 
    return result;
}

sf::Vector2i Pathfinder::WorldToCell(sf::Vector2f pos, sf::Vector2f grid_size)
{
    return {
        static_cast<int>(std::floor(pos.x / grid_size.x)),
        static_cast<int>(std::floor(pos.y / grid_size.y))
    };
}

sf::Vector2f Pathfinder::CellToWorld(sf::Vector2i cell, sf::Vector2f grid_size)
{
    return {
        (cell.x + 0.5f) * grid_size.x,
        (cell.y + 0.5f) * grid_size.y
    };
}

float Pathfinder::Heuristic(sf::Vector2i a, sf::Vector2i b)
{
    int dx = std::abs(a.x - b.x);
    int dy = std::abs(a.y - b.y);
    return static_cast<float>(dx + dy) + (std::sqrt(2.f) - 2.f) * static_cast<float>(std::min(dx, dy));
}

std::vector<sf::Vector2i> Pathfinder::Neighbours(sf::Vector2i cell)
{
    return {
        {cell.x + 1, cell.y}, {cell.x - 1, cell.y},
        {cell.x, cell.y + 1}, {cell.x, cell.y - 1},
        {cell.x + 1, cell.y}, {cell.x - 1, cell.y - 1},
        {cell.x + 1, cell.y - 1}, {cell.x - 1, cell.y + 1}
    };
}
