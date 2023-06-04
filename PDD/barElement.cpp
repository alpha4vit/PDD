#include "barElement.h"

barElement::barElement(int number, int x, int y)
{
    RectangleShape rect;
    rect.setPosition(x, y);
    rect.setSize(*new Vector2f(50, 50));
    rect.setFillColor(Color::Red);
}

bool barElement::isMouseOver(RenderWindow& window)
{
    Vector2i mousePos = Mouse::getPosition(window);
    if (mousePos.x > this->rect.getPosition().x && mousePos.x < this->rect.getPosition().x + rect.getLocalBounds().width
        && mousePos.y > this->rect.getPosition().y && mousePos.y < this->rect.getPosition().y + rect.getLocalBounds().height)
        return true;
    else
        return false;
}
