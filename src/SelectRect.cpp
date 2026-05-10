#include "SelectRect.h"

#include "managers/SelectionManager.h"

SelectRect::SelectRect(sf::Vector2f pos, sf::Vector2f size)
    : rect(size), startedSelection(false)
{
    rect.setPosition(pos);

    rect.setFillColor(sf::Color(0, 255, 0, 50));
    rect.setOutlineColor(sf::Color::Green);
    rect.setOutlineThickness(0.5f);
}

SelectRect::~SelectRect()
{
}

void SelectRect::UpdateRect(sf::Vector2f startPos, sf::Vector2f currentPos)
{
    float left = std::min(startPos.x, currentPos.x);
    float top = std::min(startPos.y, currentPos.y);

    float width = std::abs(currentPos.x - startPos.x);
    float height = std::abs(currentPos.y - startPos.y);

    rect.setPosition({left, top});
    rect.setSize({width, height});
}

void SelectRect::Render(sf::RenderTarget &target)
{
    target.draw(rect);
}

sf::Vector2f SelectRect::GetSelectionStart()
{
    return selectionStart;
}

sf::Vector2f SelectRect::GetPos()
{
    return rect.getPosition();
}

sf::Vector2f SelectRect::GetSize()
{
    return rect.getSize();
}

bool SelectRect::GetStartedSelection()
{
    return startedSelection;
}

void SelectRect::SetSelectionStart(sf::Vector2f pos)
{
    selectionStart = pos;
}

void SelectRect::SetPos(sf::Vector2f pos)
{
    rect.setPosition(pos);
}

void SelectRect::SetSize(sf::Vector2f size)
{
    rect.setSize(size);
}

void SelectRect::SetStartedSelection(bool startedSelection)
{
    this->startedSelection = startedSelection;
}

void SelectRect::SelectUnits(sf::RenderWindow& window, sf::View& view, SelectionManager &selectionManager, std::vector<GameObject*>& objects)
{
    sf::FloatRect selectionBounds = rect.getGlobalBounds();

    for (auto* object : objects)
    {
        Unit* unit = dynamic_cast<Unit*>(object);
        if (!unit)
            continue;

        if (selectionBounds.contains(unit->GetPos()))
        {
            selectionManager.AddSelect(unit);
            unit->SetIsSelected(true);
        }
        else
        {
            selectionManager.ClearSelected(unit);
            unit->SetIsSelected(false);
        }
    }
}

void SelectRect::Reset()
{
    rect.setPosition({});
    rect.setSize({});
    startedSelection = false;
}
