#include"includes.h"
#include"Object.h"
#include<SFML/Audio/Music.hpp>

void mainMenu(RenderWindow& window, Music& music);
void settings(RenderWindow& window, Music& music);
int readVolumeFromFile();
void writeVolumeToFile(int volume);
void rules(RenderWindow& app, Music& music);
void readCaptures(vector<Text>& captures);
void showCaptures(RenderWindow& app, vector<Text>& captures, Vector2f& vec);
bool isMouseOver(RenderWindow& window, Text text);
void mergeCapture(vector<Text>& captures, string& temp, int x, int& y, int i);
void firstCapture(RenderWindow& app, Music& music);
int main()
{
    setlocale(LC_ALL, "ru");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Music music;
    sf::RenderWindow app(sf::VideoMode(1000, 1000), L"Дорожные правила");
    music.openFromFile("src\\sounds\\backsound.ogg");
    music.play();
    music.setLoop(true);
    // setting icon
    Image icon = *new Image();
    icon.loadFromFile("src\\logo.png");
    app.setIcon(275, 242, icon.getPixelsPtr());

    mainMenu(app, music);

}


void mainMenu(RenderWindow& app, Music& music) {


    Object bg = *new Object("src\\bg\\bg3.jpg", *new Vector2f(0, 0));
    Object buttonRules = *new Object("src\\buttons\\rules.png", *new Vector2f(250, 300));
    Object buttonSigns = *new Object("src\\buttons\\signs.png", *new Vector2f(250, 470));
    Object buttonTest = *new Object("src\\buttons\\test.jpg", *new Vector2f(250, 640));
    Object buttonMarkup = *new Object("src\\buttons\\markup.jpg", *new Vector2f(250, 810));
    Font font;
    font.loadFromFile("src\\Gagalin-Regular.otf");
    Text title(L"ДОРОЖНЫЕ ПРАВИЛА", font, 72);
    title.setPosition(*new Vector2f(180, 100));
    title.setFillColor(Color::Black);

    while (app.isOpen())
    {
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                app.close();
        }


        buttonRules.sprite.setPosition(*new Vector2f(250, 300));
        buttonRules.sprite.setScale(*new Vector2f(1, 1));
        buttonSigns.sprite.setScale(*new Vector2f(1, 1));
        buttonSigns.sprite.setPosition(*new Vector2f(250, 470));
        buttonTest.sprite.setScale(*new Vector2f(1, 1));
        buttonTest.sprite.setPosition(*new Vector2f(250, 640));
        buttonMarkup.sprite.setScale(*new Vector2f(1, 1));
        buttonMarkup.sprite.setPosition(*new Vector2f(250, 810));
        Object buttonSettings = *new Object("src\\buttons\\settings.png", *new Vector2f(900, 20));

        app.clear();
        app.draw(bg.sprite);
        app.draw(title);

        if (buttonRules.isMouseOver(app)) {
            Vector2f tempPos = buttonRules.sprite.getPosition();
            buttonRules.sprite.setScale(*new Vector2f(1.05, 1.05));
            buttonRules.sprite.setPosition(*new Vector2f(tempPos.x - 12, tempPos.y - 5));
        }
        app.draw(buttonRules.sprite);

        if (buttonTest.isMouseOver(app)) {
            Vector2f tempPos = buttonTest.sprite.getPosition();
            buttonTest.sprite.setScale(*new Vector2f(1.05, 1.05));
            buttonTest.sprite.setPosition(*new Vector2f(tempPos.x - 12, tempPos.y - 5));
        }
        app.draw(buttonTest.sprite);

        if (buttonSigns.isMouseOver(app)) {
            Vector2f tempPos = buttonSigns.sprite.getPosition();
            buttonSigns.sprite.setScale(*new Vector2f(1.05, 1.05));
            buttonSigns.sprite.setPosition(*new Vector2f(tempPos.x - 12, tempPos.y - 5));
        }
        app.draw(buttonSigns.sprite);

        if (buttonMarkup.isMouseOver(app)) {
            Vector2f tempPos = buttonMarkup.sprite.getPosition();
            buttonMarkup.sprite.setScale(*new Vector2f(1.05, 1.05));
            buttonMarkup.sprite.setPosition(*new Vector2f(tempPos.x - 12, tempPos.y - 5));
        }
        if (buttonSettings.isMouseOver(app)) {
            Vector2f tempPos = buttonSettings.sprite.getPosition();
            buttonSettings.sprite.setScale(*new Vector2f(1.05, 1.05));
            buttonSettings.sprite.setPosition(*new Vector2f(tempPos.x - 2, tempPos.y - 2));
        }
        app.draw(buttonSettings.sprite);
        app.draw(buttonMarkup.sprite);

        if (Mouse::isButtonPressed(Mouse::Left)) {
            if (buttonRules.isMouseOver(app)) {
                rules(app, music);
            }
            else if (buttonTest.isMouseOver(app)) {

            }
            else if (buttonSigns.isMouseOver(app)) {

            }
            else if (buttonSigns.isMouseOver(app)) {

            }
            else if (buttonSettings.isMouseOver(app)) {
                settings(app, music);
            }
        }

        app.display();
    }

}


void settings(RenderWindow& window, Music& music) {

    Object bg = *new Object("src\\bg\\bg3.jpg", *new Vector2f(0, 0));
    
    Font font;
    font.loadFromFile("src\\Gagalin-Regular.otf");
    Text title(L"НАСТРОЙКИ", font, 92);
    title.setPosition(*new Vector2f(280, 40));
    title.setFillColor(Color::Black);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        Object homeButton = *new Object("src\\buttons\\home.png", *new Vector2f(900, 20));
 

        window.clear();
        if (homeButton.isMouseOver(window)) {
            Vector2f tempPos = homeButton.sprite.getPosition();
            homeButton.sprite.setScale(*new Vector2f(1.05, 1.05));
            homeButton.sprite.setPosition(*new Vector2f(tempPos.x - 2, tempPos.y - 2));
        }

        if (Mouse::isButtonPressed(Mouse::Left)) {
            if (homeButton.isMouseOver(window)) {
                mainMenu(window, music);
            }
        }

        window.draw(bg.sprite);
        window.draw(title);
        window.draw(homeButton.sprite);


        window.display();
    }
}


void rules(RenderWindow& app, Music& music) {
    Object bg = *new Object("src\\bg\\bg3.jpg", *new Vector2f(0, 0));
    sf::Vector2f textPosition(10, 10);
    sf::Vector2f scrollPosition(0, 0);
    float scrollSpeed = 20.0f;
    vector<Text> captures;
    readCaptures(captures);

    float windowWidth = static_cast<float>(app.getSize().x);
    float windowHeight = static_cast<float>(app.getSize().y);

    while (app.isOpen())
    {
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                app.close();
            else if (event.type == sf::Event::MouseWheelScrolled)
            {
                if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
                {
                    if (event.mouseWheelScroll.delta < 0)
                    {
                        cout << "вниз " << endl;
                        Text temp = captures[captures.size() - 1];
                        if (temp.getPosition().y > 950) {
                            for (int i = 0; i < captures.size(); ++i) {
                                Vector2f pos = captures[i].getPosition();
                                captures[i].setPosition(*new Vector2f(pos.x, pos.y - 20));
                            }
                        }
                    }
                    else if (event.mouseWheelScroll.delta > 0)
                    {
                        cout << "вверх " << endl;
                        Text temp = captures[0];
                        if (temp.getPosition().y < 20) {
                            for (int i = 0; i < captures.size(); ++i) {
                                Vector2f pos = captures[i].getPosition();
                                captures[i].setPosition(*new Vector2f(pos.x, pos.y + 20));
                            }
                        }
                    }
                }
            }

        }



        Object homeButton = *new Object("src\\buttons\\home.png", *new Vector2f(900, 20));

        app.clear();

        if (homeButton.isMouseOver(app)) {
            Vector2f tempPos = homeButton.sprite.getPosition();
            homeButton.sprite.setScale(*new Vector2f(1.05, 1.05));
            homeButton.sprite.setPosition(*new Vector2f(tempPos.x - 2, tempPos.y - 2));
        }

        if (Mouse::isButtonPressed(Mouse::Left)) {
            if (homeButton.isMouseOver(app)) {
                mainMenu(app, music);
            }
            for (int i = 0; i < captures.size(); ++i) {
                if (isMouseOver(app, captures[i])) {
                    cout << "dsadsa";
                }
            }
        }



        app.draw(bg.sprite);
        app.draw(homeButton.sprite);
        showCaptures(app, captures, *new Vector2f(windowWidth, windowHeight));
        app.display();
    }
}


void showCaptures(RenderWindow& app, vector<Text>& captures, Vector2f& vec) {
    Font font;
    font.loadFromFile("src\\Gagalin-Regular.otf");
    for (int i = 0; i < captures.size(); ++i) {

        captures[i].setFont(font);
        

        if (isMouseOver(app, captures[i])) {
            Text temp(captures[i]);
            temp.setScale(1.05f, 1.05f);
            temp.setPosition(captures[i].getPosition().x - 2.f, captures[i].getPosition().y - 2.f);
            temp.setFillColor(Color::Blue);
            if (i == 7 || i ==14 || i == 23 || i == 28 || i ==30) {
                Text temp1(captures[i+1]);
                temp1.setScale(1.05f, 1.05f);
                temp1.setPosition(captures[i+1].getPosition().x - 2.f, captures[i+1].getPosition().y - 2.f);
                temp1.setFillColor(Color::Blue);
                app.draw(temp1);
                i++;
            }
            else if (i == 8 || i ==15 || i == 24 || i == 29 || i == 31) {
                Texture texture;
                texture.loadFromFile("src\\bg\\bg3.jpg");
                Sprite rect;
                rect.setTexture(texture);
                rect.setTextureRect(IntRect(captures[i - 1].getPosition().x, captures[i - 1].getPosition().y, captures[i - 1].getLocalBounds().width, captures[i - 1].getLocalBounds().height + 5));
                rect.setPosition(captures[i - 1].getPosition());
                app.draw(rect);
                Text temp1(captures[i - 1]);
                temp1.setScale(1.05f, 1.05f);
                temp1.setPosition(captures[i - 1].getPosition().x - 2.f, captures[i - 1].getPosition().y - 2.f);
                temp1.setFillColor(Color::Blue);
                app.draw(temp1);
            }
            app.draw(temp);
        }
        else
            app.draw(captures[i]);
    }
}

void readCaptures(vector<Text>& captures) {
    int x = 30;
    int y = 40;
    Font font;
    font.loadFromFile("src\\Gagalin-Regular.otf");
    fstream file;
    file.imbue(std::locale(""));
    file.open("captures.txt");
    for (int i = 0; i < 27; ++i) {
        string temp;
        getline(file, temp);
        switch (i)
        {
        case 7: {
            mergeCapture(captures, temp, x, y, i);
            continue; break;
        }
        case 13: {
            mergeCapture(captures, temp, x, y, i);
            continue; break;
        }
        case 21: {
            mergeCapture(captures, temp, x, y, i);
            continue; break;
        }
        case 25: {
            mergeCapture(captures, temp, x, y, i);
            continue; break;
        }
        case 26: {
            mergeCapture(captures, temp, x, y, i);
            continue; break;
        }
        default:
            break;
        }
        Text textTemp(sf::String::fromUtf8(temp.begin(), temp.end()), font, 22);
        textTemp.setFillColor(Color::Black);
        textTemp.setPosition(*new Vector2f(x, y));
        y += 35;
        captures.push_back(textTemp);
    }
    file.close();
}


void writeVolumeToFile(int volume) {
    ofstream file;
    file.open("properties.txt");
    file.clear();
    file << volume;
    file.close();
}

int readVolumeFromFile() {
    int temp;
    fstream file;
    file.open("properties.txt");
    file >> temp;
    file.close();
    return temp;
}

bool isMouseOver(RenderWindow& window, Text text)
{
    Vector2i mousePos = Mouse::getPosition(window);
    if (mousePos.x > text.getPosition().x && mousePos.x < text.getPosition().x + text.getLocalBounds().width + 3
        && mousePos.y > text.getPosition().y && mousePos.y < text.getPosition().y + text.getLocalBounds().height + 3)
        return true;
    else
        return false;
}

void mergeCapture(vector<Text>& captures, string& temp, int x, int& y, int i) {
    int sizeFpart = 79;
    if (i == 13)
        sizeFpart = 75;
    else if (i == 21)
        sizeFpart = 73;
    else if (i == 25)
        sizeFpart = 80;
    else if (i == 26) {
        sizeFpart = 73;
    }
    Font font;
    font.loadFromFile("src\\Gagalin-Regular.otf");
    Text temp1(sf::String::fromUtf8(temp.begin(), temp.end()).substring(0, sizeFpart), font, 22);
    temp1.setFillColor(Color::Black);
    temp1.setPosition(*new Vector2f(x, y));
    y += 35;
    Text temp2(sf::String::fromUtf8(temp.begin(), temp.end()).substring(sizeFpart), font, 22);
    temp2.setFillColor(Color::Black);
    temp2.setPosition(*new Vector2f(x, y));
    y += 35;
    captures.push_back(temp1);
    captures.push_back(temp2);
}

void firstCapture(RenderWindow& app, Music& music) {
    Texture texture;
    texture.loadFromFile("src\\try.png");
    Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(0.f, 0.f);
    app.draw(sprite);
}