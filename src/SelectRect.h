#pragma once

#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/View.hpp>

class SelectionManager;
class GameObject;

class SelectRect
{
public:
    SelectRect(sf::Vector2f pos = {}, sf::Vector2f size = {});
    ~SelectRect();

    void UpdateRect(sf::Vector2f start_pos, sf::Vector2f current_pos);
    void Render(sf::RenderTarget& target);

    sf::Vector2f GetSelectionStart();
    sf::Vector2f GetPos();
    sf::Vector2f GetSize();
    bool GetStartedSelection();

    void SetSelectionStart(sf::Vector2f pos);
    void SetPos(sf::Vector2f pos);
    void SetSize(sf::Vector2f size);
    void SetStartedSelection(bool started_selection);

    void SelectUnits(sf::RenderWindow& window, sf::View& view, SelectionManager& selection_manager, std::vector<GameObject*>& objects);

    void Reset();

private:
    sf::RectangleShape rect;
    sf::Vector2f selectionStart;
    bool startedSelection;
};
