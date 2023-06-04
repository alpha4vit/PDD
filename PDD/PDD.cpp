#include"includes.h"
#include"Object.h"
#include<SFML/Audio/Music.hpp>
#include"selfText.h"
#include"image.h"
#include"test.h"
void mainMenu(RenderWindow& window, Music& music);
void settings(RenderWindow& window, Music& music);
int readVolumeFromFile();
void writeVolumeToFile(int volume);
void rules(RenderWindow& app, Music& music);
void readCaptures(vector<selfText>& captures, int type);
void showCaptures(RenderWindow& app, vector<selfText>& captures, Vector2f& vec, int type);
bool isMouseOver(RenderWindow& window, selfText text);
bool isMouseOver(RenderWindow& window, RectangleShape rect);
void mergeCapture(vector<selfText>& captures, string& temp, int x, int& y, int i);
void showCapture(RenderWindow& window, Music& music, int captureNum, int type);
void signs(RenderWindow& app, Music& music);
void markup(RenderWindow& app, Music& music);
void tests(RenderWindow& app, Music& music);
void getNumTests(vector<test>& tests);
vector<RectangleShape> genProgressBar(vector<test>& tests);
void drawBarNum(RenderWindow& window, vector<RectangleShape>& bar);
void showCaptures(RenderWindow& app, test& test);


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
                tests(app, music);
            }
            else if (buttonSigns.isMouseOver(app)) {
                signs(app, music);
            }
            else if (buttonMarkup.isMouseOver(app)) {
                markup(app, music);
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
    vector<selfText> captures;
    readCaptures(captures, 0);

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
                        Text temp = captures[captures.size() - 1].text;
                        if (temp.getPosition().y > 950) {
                            for (int i = 0; i < captures.size(); ++i) {
                                Vector2f pos = captures[i].text.getPosition();
                                captures[i].text.setPosition(*new Vector2f(pos.x, pos.y - 35));
                            }
                        }
                    }
                    else if (event.mouseWheelScroll.delta > 0)
                    {
                        cout << "вверх " << endl;
                        Text temp = captures[0].text;
                        if (temp.getPosition().y < 20) {
                            for (int i = 0; i < captures.size(); ++i) {
                                Vector2f pos = captures[i].text.getPosition();
                                captures[i].text.setPosition(*new Vector2f(pos.x, pos.y + 35));
                            }
                        }
                    }
                }
            }

        }



        Object homeButton = *new Object("src\\buttons\\home.png", *new Vector2f(900, 20));

        app.clear();
        app.draw(bg.sprite);


        if (homeButton.isMouseOver(app)) {
            Vector2f tempPos = homeButton.sprite.getPosition();
            homeButton.sprite.setScale(*new Vector2f(1.05, 1.05));
            homeButton.sprite.setPosition(*new Vector2f(tempPos.x - 2, tempPos.y - 2));
        }

        app.draw(homeButton.sprite);

        if (Mouse::isButtonPressed(Mouse::Left)) {
            if (homeButton.isMouseOver(app)) {
                mainMenu(app, music);
            }
            else {
                for (int i = 0; i < captures.size(); ++i) {
                    if (isMouseOver(app, captures[i])) {
                        showCapture(app, music, i, 0);
                    }
                }
            }
        }



        
        showCaptures(app, captures, *new Vector2f(windowWidth, windowHeight), 0);
        app.display();
    }
}

void signs(RenderWindow& app, Music& music) {
    Object bg = *new Object("src\\bg\\bg3.jpg", *new Vector2f(0, 0));
    sf::Vector2f textPosition(10, 10);
    sf::Vector2f scrollPosition(0, 0);
    float scrollSpeed = 20.0f;
    vector<selfText> captures;
    readCaptures(captures, 1);

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
                        Text temp = captures[captures.size() - 1].text;
                        if (temp.getPosition().y > 950) {
                            for (int i = 0; i < captures.size(); ++i) {
                                Vector2f pos = captures[i].text.getPosition();
                                captures[i].text.setPosition(*new Vector2f(pos.x, pos.y - 35));
                            }
                        }
                    }
                    else if (event.mouseWheelScroll.delta > 0)
                    {
                        cout << "вверх " << endl;
                        Text temp = captures[0].text;
                        if (temp.getPosition().y < 20) {
                            for (int i = 0; i < captures.size(); ++i) {
                                Vector2f pos = captures[i].text.getPosition();
                                captures[i].text.setPosition(*new Vector2f(pos.x, pos.y + 35));
                            }
                        }
                    }
                }
            }

        }



        Object homeButton = *new Object("src\\buttons\\home.png", *new Vector2f(900, 20));


        app.clear();
        app.draw(bg.sprite);
        app.draw(homeButton.sprite);

        if (homeButton.isMouseOver(app)) {
            Vector2f tempPos = homeButton.sprite.getPosition();
            homeButton.sprite.setScale(*new Vector2f(1.05, 1.05));
            homeButton.sprite.setPosition(*new Vector2f(tempPos.x - 2, tempPos.y - 2));
        }

        if (Mouse::isButtonPressed(Mouse::Left)) {
            if (homeButton.isMouseOver(app)) {
                mainMenu(app, music);
            }
            else {
                for (int i = 0; i < captures.size(); ++i) {
                    if (isMouseOver(app, captures[i])) {
                        showCapture(app, music, i, 1);
                    }
                }
            }
        }




        showCaptures(app, captures, *new Vector2f(windowWidth, windowHeight), 1);
        app.display();
    }
}


void showCaptures(RenderWindow& app, vector<selfText>& captures, Vector2f& vec, int type) {

    Font font;
    font.loadFromFile("src\\Gagalin-Regular.otf");
    for (int i = 0; i < captures.size(); ++i) {

        captures[i].text.setFont(font);
        

        if (isMouseOver(app, captures[i])) {
            Text temp(captures[i].text);
            temp.setScale(1.05f, 1.05f);
            temp.setPosition(captures[i].text.getPosition().x - 2.f, captures[i].text.getPosition().y - 2.f);
            temp.setFillColor(Color::Blue);
            if (type ==0 && i == 7 || i ==14 || i == 23 || i == 28 || i ==30) {
                Text temp1(captures[i+1].text);
                temp1.setScale(1.05f, 1.05f);
                temp1.setPosition(captures[i+1].text.getPosition().x - 2.f, captures[i+1].text.getPosition().y - 2.f);
                temp1.setFillColor(Color::Blue);
                app.draw(temp1);
                i++;
            }
            else if (type ==0 && i == 8 || i ==15 || i == 24 || i == 29 || i == 31) {
                Texture texture;
                texture.loadFromFile("src\\bg\\bg3.jpg");
                Sprite rect;
                rect.setTexture(texture);
                rect.setTextureRect(IntRect(captures[i - 1].text.getPosition().x, captures[i - 1].text.getPosition().y, captures[i - 1].text.getLocalBounds().width, captures[i - 1].text.getLocalBounds().height + 5));
                rect.setPosition(captures[i - 1].text.getPosition());
                app.draw(rect);
                Text temp1(captures[i - 1].text);
                temp1.setScale(1.05f, 1.05f);
                temp1.setPosition(captures[i - 1].text.getPosition().x - 2.f, captures[i - 1].text.getPosition().y - 2.f);
                temp1.setFillColor(Color::Blue);
                app.draw(temp1);
            }
            app.draw(temp);
        }
        else
            app.draw(captures[i].text);
    }
}

void readCaptures(vector<selfText>& captures, int type) {
    int size = 27;
    if (type == 1)
        size = 8;
    else if (type == 2) {
        size = 3;
    }
    int x = 30;
    int y = 40;
    Font font;
    font.loadFromFile("src\\Gagalin-Regular.otf");
    fstream file;
    file.imbue(std::locale(""));
    if (type == 0)
        file.open("captures.txt");
    else if (type == 1)
        file.open("rulesParagraphs.txt");
    else if (type == 2) {
        file.open("markup.txt");
    }
    for (int i = 0; i < size; ++i) {
        string temp;
        getline(file, temp);
        if (type == 0) {
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
        }
        Text textTemp(sf::String::fromUtf8(temp.begin(), temp.end()), font, 22);
        textTemp.setFillColor(Color::Black);
        textTemp.setPosition(*new Vector2f(x, y));
        y += 35;
        captures.push_back(selfText(textTemp));
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

bool isMouseOver(RenderWindow& window, selfText text)
{
    Vector2i mousePos = Mouse::getPosition(window);

    if (mousePos.x > text.text.getPosition().x && mousePos.x < text.text.getPosition().x + text.bounds.width + 3
        && mousePos.y > text.text.getPosition().y && mousePos.y < text.text.getPosition().y + text.bounds.height + 3) 
        return true;
    else
        return false;
}

bool isMouseOver(RenderWindow& window, RectangleShape rect)
{
    Vector2i mousePos = Mouse::getPosition(window);
    FloatRect bounds = rect.getLocalBounds();
    if (mousePos.x > rect.getPosition().x && mousePos.x < rect.getPosition().x + bounds.width
        && mousePos.y > rect.getPosition().y && mousePos.y < rect.getPosition().y +bounds.height)
        return true;
    else
        return false;
}

void mergeCapture(vector<selfText>& captures, string& temp, int x, int& y, int i) {
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
    captures.push_back(selfText(temp1));
    captures.push_back(selfText(temp2));
}

void showCapture(RenderWindow& window, Music& music, int captureNum, int type) {

    Object bg = *new Object("src\\bg\\bg3.jpg", *new Vector2f(0, 0));
    
    vector<image> rulesPic;
    fillVector(captureNum, rulesPic, type);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();


            if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
            {
                if (event.mouseWheelScroll.delta < 0)
                {
                    cout << "вниз " << endl;
                    if (rulesPic[rulesPic.size() - 1].sprite.getPosition().y + rulesPic[rulesPic.size() - 1].sprite.getLocalBounds().height > 980) {
                        for (int i = 0; i < rulesPic.size(); ++i) {
                            Vector2f pos = rulesPic[i].sprite.getPosition();
                            rulesPic[i].sprite.setPosition(*new Vector2f(pos.x, pos.y-20));
                        }
                    }
                }
                else if (event.mouseWheelScroll.delta > 0)
                {
                    cout << "вверх " << endl;
                    if (rulesPic[0].sprite.getPosition().y < 20) {
                        for (int i = 0; i < rulesPic.size(); ++i) {
                            Vector2f pos = rulesPic[i].sprite.getPosition();
                            rulesPic[i].sprite.setPosition(*new Vector2f(pos.x, pos.y + 20));
                        }
                    }
                    cout << "dsadsa";
                }
            }
        }


        window.clear();

        Object homeButton = *new Object("src\\buttons\\home.png", *new Vector2f(900, 20));
        Object backButton = *new Object("src\\buttons\\arrowBack.png", *new Vector2f(900, 100));

        window.draw(bg.sprite);


        if (homeButton.isMouseOver(window)) {
            Vector2f tempPos = homeButton.sprite.getPosition();
            homeButton.sprite.setScale(*new Vector2f(1.05, 1.05));
            homeButton.sprite.setPosition(*new Vector2f(tempPos.x - 2, tempPos.y - 2));
        }
        else if (backButton.isMouseOver(window)) {
            Vector2f tempPos = backButton.sprite.getPosition();
            backButton.sprite.setScale(*new Vector2f(1.05, 1.05));
            backButton.sprite.setPosition(*new Vector2f(tempPos.x - 2, tempPos.y - 2));
        }


        if (Mouse::isButtonPressed(Mouse::Left)) {
            if (homeButton.isMouseOver(window)) {
                mainMenu(window, music);
            }
            else if (backButton.isMouseOver(window)) {
                if (type == 0) {
                    rules(window, music);
                }
                else if (type == 1) {
                    signs(window, music);
                }
                else if (type == 2) {
                    markup(window, music);
                }
            }
        }



        for (int i = 0; i < rulesPic.size(); ++i) {
            window.draw(rulesPic[i].sprite);
        }
        window.draw(homeButton.sprite);
        window.draw(backButton.sprite);
  

        window.display();
    }
}

void markup(RenderWindow& app, Music& music) {
    Object bg = *new Object("src\\bg\\bg3.jpg", *new Vector2f(0, 0));
    sf::Vector2f textPosition(10, 10);
    sf::Vector2f scrollPosition(0, 0);
    float scrollSpeed = 20.0f;
    vector<selfText> captures;
    readCaptures(captures, 2);

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
                        Text temp = captures[captures.size() - 1].text;
                        if (temp.getPosition().y > 950) {
                            for (int i = 0; i < captures.size(); ++i) {
                                Vector2f pos = captures[i].text.getPosition();
                                captures[i].text.setPosition(*new Vector2f(pos.x, pos.y - 35));
                            }
                        }
                    }
                    else if (event.mouseWheelScroll.delta > 0)
                    {
                        cout << "вверх " << endl;
                        Text temp = captures[0].text;
                        if (temp.getPosition().y < 20) {
                            for (int i = 0; i < captures.size(); ++i) {
                                Vector2f pos = captures[i].text.getPosition();
                                captures[i].text.setPosition(*new Vector2f(pos.x, pos.y + 35));
                            }
                        }
                    }
                }
            }

        }



        Object homeButton = *new Object("src\\buttons\\home.png", *new Vector2f(900, 20));


        app.clear();
        app.draw(bg.sprite);
        

        if (homeButton.isMouseOver(app)) {
            Vector2f tempPos = homeButton.sprite.getPosition();
            homeButton.sprite.setScale(*new Vector2f(1.05, 1.05));
            homeButton.sprite.setPosition(*new Vector2f(tempPos.x - 2, tempPos.y - 2));
        }
        app.draw(homeButton.sprite);

        if (Mouse::isButtonPressed(Mouse::Left)) {
            if (homeButton.isMouseOver(app)) {
                mainMenu(app, music);
            }
            else {
                for (int i = 0; i < captures.size(); ++i) {
                    if (isMouseOver(app, captures[i])) {
                        showCapture(app, music, i, 2);
                    }
                }
            }
        }


        showCaptures(app, captures, *new Vector2f(windowWidth, windowHeight), 2);
        app.display();
    }
}


void tests(RenderWindow& app, Music& music) {
    Object bg = *new Object("src\\bg\\bg3.jpg", *new Vector2f(0, 0));
    Object rightArrow = *new Object("src\\buttons\\rightArrow.png", *new Vector2f(750, 850));
    Object leftArrow = *new Object("src\\buttons\\leftArrow.png", *new Vector2f(50, 850));
    sf::Vector2f textPosition(10, 10);
    sf::Vector2f scrollPosition(0, 0);
    float scrollSpeed = 20.0f;
    vector<test> tests;
    getNumTests(tests);
    vector<RectangleShape> bar = genProgressBar(tests);

    float windowWidth = static_cast<float>(app.getSize().x);
    float windowHeight = static_cast<float>(app.getSize().y);
    int index = 0;
    bool isKeyButtonReleased = true;

    while (app.isOpen())
    {
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                app.close();
            if (event.type == sf::Event::MouseWheelScrolled)
            {
                if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
                {
                    if (event.mouseWheelScroll.delta < 0)
                    {
                        cout << "вниз " << endl;
                        
                    }
                    else if (event.mouseWheelScroll.delta > 0)
                    {
                        cout << "вверх " << endl;
                        
                    }
                }
            }
            if (event.type == Event::MouseButtonReleased) {
                if (event.key.code == Mouse::Left) {
                    isKeyButtonReleased = true;
                }
            }

        }



        Object homeButton = *new Object("src\\buttons\\home.png", *new Vector2f(900, 20));
        rightArrow.sprite.setScale(1.f, 1.f);
        rightArrow.sprite.setPosition(750.f, 850.f);
        leftArrow.sprite.setScale(1.f, 1.f);
        leftArrow.sprite.setPosition(50.f, 850.f);

        app.clear();
        app.draw(bg.sprite);

        for (int i = 0; i < bar.size(); ++i) {
            if (i == index)
                bar[i].setFillColor(Color::Black);
            else if (tests[i].state) 
                bar[i].setFillColor(Color::Green);
            else
                bar[i].setFillColor(Color::Red);
            if (isMouseOver(app, bar[i])) {
                if (tests[i].state)
                    bar[i].setFillColor(Color(13, 94, 4));
                else
                    bar[i].setFillColor(Color(117, 10, 8));
                app.draw(bar[i]);
            }
            else
                app.draw(bar[i]);
        }

        if (homeButton.isMouseOver(app)) {
            Vector2f tempPos = homeButton.sprite.getPosition();
            homeButton.sprite.setScale(*new Vector2f(1.02, 1.02));
            homeButton.sprite.setPosition(*new Vector2f(tempPos.x - 2, tempPos.y - 2));
        }
        else if (rightArrow.isMouseOver(app)) {
            Vector2f tempPos = rightArrow.sprite.getPosition();
            rightArrow.sprite.setScale(*new Vector2f(1.02, 1.02));
            rightArrow.sprite.setPosition(*new Vector2f(tempPos.x - 2, tempPos.y - 2));
        }
        else if (leftArrow.isMouseOver(app)) {
            Vector2f tempPos = leftArrow.sprite.getPosition();
            leftArrow.sprite.setScale(*new Vector2f(1.02, 1.02));
            leftArrow.sprite.setPosition(*new Vector2f(tempPos.x - 2, tempPos.y - 2));
        }

        app.draw(homeButton.sprite);
        app.draw(rightArrow.sprite);
        app.draw(leftArrow.sprite);


        app.draw(tests[index].task.sprite);
        showCaptures(app,tests[index]);
        
        if (Mouse::isButtonPressed(Mouse::Left) && isKeyButtonReleased) {
            if (homeButton.isMouseOver(app)) {
                mainMenu(app, music);
            }
            else if (rightArrow.isMouseOver(app) && index < 9) {
                index++;
                cout << index << endl;
            }
            else if (leftArrow.isMouseOver(app) && index > 0) {
                index--;
                cout << index << endl;
            }
            else {
                for (int i = 0; i < tests[index].answers.size(); ++i) {
                    if (isMouseOver(app, tests[index].answers[i])) {
                        if (tests[index].answers[i].text.getString() == tests[index].correctAnswer) {
                            tests[index].state = true;
                            ++index;
                            cout << true << endl;
                        }
                        else {
                            cout << false << endl;
                            ++index;
                        }
                    }
                    if (index == 9) { // TODO при последнем вопросе сделать окно
                       
                    }

                }
                for (int i = 0; i < bar.size(); ++i) {
                    if (isMouseOver(app, bar[i])) {
                        index = i;
                    }
                }
            }
            isKeyButtonReleased = false;
        }
        drawBarNum(app, bar);
        
        
        
        app.display();
    }
}


void getNumTests(vector<test>& tests) {
    srand(time(NULL));
    vector<int> nums;
    bool fl = false;
    for (int i = 0; i < 10; ++i) {
        int temp = 1 + rand() % 14;
        for (int j = 0; j < nums.size(); ++j) {
            if (nums[j] == temp) {
                fl = true; break;
            }
        }
        if (fl) {
            --i; fl = false; continue;
        }
        nums.push_back(temp);
        tests.push_back(*new test(temp));
    }
}

vector<RectangleShape> genProgressBar(vector<test>& tests) {
    vector<RectangleShape> bar;
    int x = 241, y = 0, step = 50;
    for (int i = 0; i < tests.size(); ++i) {
        RectangleShape rect;
        rect.setPosition(x, y);
        rect.setSize(*new Vector2f(step, step));
        rect.setFillColor(Color::Red);
        bar.push_back(rect);
        x += 51;
    }
    return bar;
}



//
//vector<selfText> mixAnswers(vector<selfText> tests) {
//    srand(time(NULL));
//    vector<selfText> mixed;
//    vector<int> nums;
//    bool fl = false;
//    for (int i = 0; i < 3; ++i) {
//        int index = 0 + rand() % 2;
//        for (int j = 0; j < nums.size(); ++j) {
//            if (nums[j] == index) {
//                fl = true; break;
//            }
//        }
//        if (fl) {
//            --i; fl = false; continue;
//        }
//        nums.push_back(index);
//        mixed.push_back(tests)
//    }
//}


void drawBarNum(RenderWindow& window, vector<RectangleShape>& bar) {
    Font font;
    font.loadFromFile("src\\Gagalin-Regular.otf");
    Text title(L"ДОРОЖНЫЕ ПРАВИЛА", font, 72);
    title.setPosition(*new Vector2f(180, 100));
    title.setFillColor(Color::Black);
    for (int i = 0; i < bar.size(); ++i) {
        Vector2f pos = bar[i].getPosition();
        Text number(to_string(i+1), font, 55);
        number.setPosition(*new Vector2f(pos.x+10, pos.y-10));
        number.setFillColor(Color::White);
        window.draw(number);
    }
}


void showCaptures(RenderWindow& app, test& test) {
    vector<selfText> answers = test.answers;
    Font font;
    font.loadFromFile("src\\Gagalin-Regular.otf");
    for (int i = 0; i < answers.size(); ++i) {

        answers[i].text.setFont(font);
        if (test.state && test.correctAnswer == answers[i].text.getString())
            answers[i].text.setFillColor(Color::Green);


        if (isMouseOver(app, answers[i]) && !test.state) {
            Text temp(answers[i].text);
            temp.setScale(1.05f, 1.05f);
            temp.setPosition(answers[i].text.getPosition().x - 2.f, answers[i].text.getPosition().y - 2.f);
            temp.setFillColor(Color::Blue);
            if (test.state && test.correctAnswer == answers[i].text.getString())
                temp.setFillColor(Color::Green);
            app.draw(temp);
        }
        else
            app.draw(answers[i].text);
    }
}
