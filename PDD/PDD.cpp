#include"includes.h"
#include"Object.h"


void mainMenu(RenderWindow& window);


int main()
{
    sf::RenderWindow app(sf::VideoMode(1000, 1000), L"Дорожные правила");

    // setting icon
    Image icon = *new Image();
    icon.loadFromFile("src\\logo.png");
    app.setIcon(275, 242, icon.getPixelsPtr());

    mainMenu(app);
}


void mainMenu(RenderWindow& app) {


    Object bg = *new Object("src\\bg\\bg3.jpg", *new Vector2f(0, 0));
    Object buttonRules = *new Object("src\\buttons\\rules.png", *new Vector2f(250, 300));
    Object buttonSigns = *new Object("src\\buttons\\signs.png", *new Vector2f(250, 470));
    Object buttonTest = *new Object("src\\buttons\\test.png", *new Vector2f(250, 640));
    Object buttonMarkup = *new Object("src\\buttons\\markup.png", *new Vector2f(250, 810));
    while (app.isOpen())
    {
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                app.close();
        }

        app.clear();
        app.draw(bg.sprite);

        if (buttonRules.isMouseOver(app)) {
            Vector2f tempPos = buttonRules.sprite.getPosition();
            buttonRules.sprite.setScale(*new Vector2f(1.05, 1.05));
            buttonRules.sprite.setPosition(*new Vector2f(tempPos.x - 5, tempPos.y - 5));
        }
        app.draw(buttonRules.sprite);

        if (buttonTest.isMouseOver(app)) {
            Vector2f tempPos = buttonTest.sprite.getPosition();
            buttonTest.sprite.setScale(*new Vector2f(1.05, 1.05));
            buttonTest.sprite.setPosition(*new Vector2f(tempPos.x - 5, tempPos.y - 5));
        }
        app.draw(buttonTest.sprite);

        if (buttonSigns.isMouseOver(app)) {
            Vector2f tempPos = buttonSigns.sprite.getPosition();
            buttonSigns.sprite.setScale(*new Vector2f(1.05, 1.05));
            buttonSigns.sprite.setPosition(*new Vector2f(tempPos.x - 5, tempPos.y - 5));
        }
        app.draw(buttonSigns.sprite);

        if (buttonMarkup.isMouseOver(app)) {
            Vector2f tempPos = buttonMarkup.sprite.getPosition();
            buttonMarkup.sprite.setScale(*new Vector2f(1.05, 1.05));
            buttonMarkup.sprite.setPosition(*new Vector2f(tempPos.x - 5, tempPos.y - 5));
        }
        app.draw(buttonMarkup.sprite);


        app.display();
    }

}