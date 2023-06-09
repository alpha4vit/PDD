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
void tests(RenderWindow& app, Music& music, int type);
void getNumTests(vector<test>& tests, int type);
vector<RectangleShape> genProgressBar(vector<test>& tests);
void drawBarNum(RenderWindow& window, vector<RectangleShape>& bar);
void showCaptures(RenderWindow& app, test& test);
void showResults(RenderWindow& app, vector<test>& tests, Music& music);
void showOption(RenderWindow& window, Music& music, bool& isOption, bool& isButtonReleased);

enum {
    signEnum, rulesEnum, markupEnum, generalEnum
};


int main()
{
    setlocale(LC_ALL, "ru");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Music music;
    sf::RenderWindow app(sf::VideoMode(1000, 1000), L"Дорожные правила");
    int volume = readVolumeFromFile();
    music.openFromFile("src\\sounds\\backsound.ogg");
    music.setVolume(volume);
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
    bool isOption = false;
    bool isButtonReleased = true;

    while (app.isOpen())
    {
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                app.close();

            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.key.code == Mouse::Left) {
                    isButtonReleased = true;
                }
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


            if (!isOption) {
                if (buttonRules.isMouseOver(app)) {
                    Vector2f tempPos = buttonRules.sprite.getPosition();
                    buttonRules.sprite.setScale(*new Vector2f(1.05, 1.05));
                    buttonRules.sprite.setPosition(*new Vector2f(tempPos.x - 12, tempPos.y - 5));
                }


                if (buttonTest.isMouseOver(app)) {
                    Vector2f tempPos = buttonTest.sprite.getPosition();
                    buttonTest.sprite.setScale(*new Vector2f(1.05, 1.05));
                    buttonTest.sprite.setPosition(*new Vector2f(tempPos.x - 12, tempPos.y - 5));
                }


                if (buttonSigns.isMouseOver(app)) {
                    Vector2f tempPos = buttonSigns.sprite.getPosition();
                    buttonSigns.sprite.setScale(*new Vector2f(1.05, 1.05));
                    buttonSigns.sprite.setPosition(*new Vector2f(tempPos.x - 12, tempPos.y - 5));
                }


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

                if (Mouse::isButtonPressed(Mouse::Left) && isButtonReleased) {
                    if (buttonRules.isMouseOver(app)) {
                        rules(app, music);
                    }
                    else if (buttonTest.isMouseOver(app)) {
                        isOption = true;
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
                    isButtonReleased = false;
                }
            }

            app.draw(buttonTest.sprite);
            app.draw(buttonSigns.sprite);
            app.draw(buttonRules.sprite);
            app.draw(buttonSettings.sprite);
            app.draw(buttonMarkup.sprite);

            if (isOption) {
                showOption(app, music, isOption, isButtonReleased);
            }


            app.display();
        }

    }
}


void settings(RenderWindow& window, Music& music) {

    Object bg = *new Object("src\\bg\\bg3.jpg", *new Vector2f(0, 0));
    Font font;
    font.loadFromFile("src\\Gagalin-Regular.otf");
    Text title(L"НАСТРОЙКИ", font, 92);
    title.setPosition(*new Vector2f(280, 40));
    title.setFillColor(Color::Black);
    bool isButtonRealesed = true;
    bool isKeyRealesed = true;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == Event::MouseButtonReleased)
                isButtonRealesed = true;
        }

        int volume = readVolumeFromFile();
        cout << volume << endl;
        Object homeButton = *new Object("src\\buttons\\home.png", *new Vector2f(900, 20));
        Object leftArrow = *new Object("src\\buttons\\arrowHeadLeft1.png", *new Vector2f(131, 298));
        Object rightArrow = *new Object("src\\buttons\\arrowHeadRight1.png", *new Vector2f(852, 298));
        RectangleShape lineMain;
        lineMain.setFillColor(Color(150, 148, 141));
        RectangleShape lineCur;
        lineCur.setFillColor(Color::Black);
        lineMain.setPosition(150, 300);
        lineCur.setPosition(150, 300);
        lineMain.setSize(*new Vector2f(700, 21));
        lineCur.setSize(*new Vector2f(volume * 7, 21));
        Text vol(to_string(volume), font, 32);
        vol.setPosition(487, 260);
        vol.setFillColor(Color::Black);
        

        window.clear();
        if (homeButton.isMouseOver(window)) {
            Vector2f tempPos = homeButton.sprite.getPosition();
            homeButton.sprite.setScale(*new Vector2f(1.05, 1.05));
            homeButton.sprite.setPosition(*new Vector2f(tempPos.x - 2, tempPos.y - 2));
        }
        if (rightArrow.isMouseOver(window)) {
            Vector2f tempPos = rightArrow.sprite.getPosition();
            rightArrow.sprite.setScale(*new Vector2f(1.05, 1.05));
            rightArrow.sprite.setPosition(*new Vector2f(tempPos.x - 1, tempPos.y - 1));
        }
        if (leftArrow.isMouseOver(window)) {
            Vector2f tempPos = leftArrow.sprite.getPosition();
            leftArrow.sprite.setScale(*new Vector2f(1.05, 1.05));
            leftArrow.sprite.setPosition(*new Vector2f(tempPos.x - 1, tempPos.y - 1));
        }
        if (Mouse::isButtonPressed(Mouse::Left) && isButtonRealesed) {
            if (homeButton.isMouseOver(window)) {
                mainMenu(window, music);
                isButtonRealesed = false;
            }
            else if (rightArrow.isMouseOver(window)) {
                if (volume + 10 <= 100)
                    writeVolumeToFile(volume + 10);
                isButtonRealesed = false;
            }
            else if (leftArrow.isMouseOver(window)) {
                if (volume - 10 >= 0)
                    writeVolumeToFile(volume - 10);
                isButtonRealesed = false;
            }
            
        }
        music.setVolume(volume);
        window.draw(bg.sprite);
        window.draw(title);
        window.draw(homeButton.sprite);
        window.draw(lineMain);
        window.draw(lineCur);
        window.draw(leftArrow.sprite);
        window.draw(rightArrow.sprite);
        window.draw(vol);

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


void showOption(RenderWindow& window, Music& music, bool& isOption, bool& isButtonReleased) {
    RectangleShape rect;
    rect.setPosition(0, 0);
    rect.setSize(*new Vector2f(1000, 1000));
    rect.setFillColor(Color(255, 255, 255, 225));
    window.draw(rect);
    Font font;
    font.loadFromFile("src\\Gagalin-Regular.otf");
    Text signTest(L"ПРОЙТИ ТЕСТ ПО ЗНАКАМ", font, 72);
    signTest.setPosition(120, 150);
    signTest.setFillColor(Color::Black);
    Text rulesTest(L"ПРОЙТИ ТЕСТ ПО ПДД", font, 72);
    rulesTest.setPosition(170, 350);
    rulesTest.setFillColor(Color::Black);
    Text generalTest(L"ПРОЙТИ ОБЩИЙ ТЕСТ", font, 72);
    generalTest.setPosition(170, 750);
    generalTest.setFillColor(Color::Black);
    Text markupTest(L"ПРОЙТИ ТЕСТ ПО РАЗМЕТКЕ", font, 72);
    markupTest.setPosition(80, 550);
    markupTest.setFillColor(Color::Black);
    if (isMouseOver(window, signTest)) {
        Vector2f pos = signTest.getPosition();
        signTest.setFillColor(Color::Blue);
        signTest.setScale(1.05f, 1.05f);
        signTest.setPosition(pos.x - 2, pos.y - 2);
    }
    else if (isMouseOver(window, rulesTest)) {
        Vector2f pos = rulesTest.getPosition();
        rulesTest.setFillColor(Color::Blue);
        rulesTest.setScale(1.05f, 1.05f);
        rulesTest.setPosition(pos.x - 2, pos.y - 2);
    }
    else if (isMouseOver(window, generalTest)) {
        Vector2f pos = generalTest.getPosition();
        generalTest.setFillColor(Color::Blue);
        generalTest.setScale(1.05f, 1.05f);
        generalTest.setPosition(pos.x - 2, pos.y - 2);
    }
    else if (isMouseOver(window, markupTest)) {
        Vector2f pos = markupTest.getPosition();
        markupTest.setFillColor(Color::Blue);
        markupTest.setScale(1.05f, 1.05f);
        markupTest.setPosition(pos.x - 2, pos.y - 2);
    }

    if (Mouse::isButtonPressed(Mouse::Left) && isButtonReleased) {
        if (isMouseOver(window, signTest)) {
            tests(window, music, signEnum);
        }
        else if (isMouseOver(window, rulesTest)) {
            tests(window, music, rulesEnum);
        }
        else if (isMouseOver(window, generalTest)) {
            tests(window, music, generalEnum);
        }
        else if (isMouseOver(window, markupTest)) {
            tests(window, music, markupEnum);
        }
        else {
            isOption = false;
        }
    }
    window.draw(signTest);
    window.draw(rulesTest);
    window.draw(generalTest);
    window.draw(markupTest);


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
                    if (rulesPic[rulesPic.size() - 1].sprite.getPosition().y + rulesPic[rulesPic.size() - 1].sprite.getLocalBounds().height > 980) {
                        for (int i = 0; i < rulesPic.size(); ++i) {
                            Vector2f pos = rulesPic[i].sprite.getPosition();
                            rulesPic[i].sprite.setPosition(*new Vector2f(pos.x, pos.y-20));
                        }
                    }
                }
                else if (event.mouseWheelScroll.delta > 0)
                {
                    if (rulesPic[0].sprite.getPosition().y < 20) {
                        for (int i = 0; i < rulesPic.size(); ++i) {
                            Vector2f pos = rulesPic[i].sprite.getPosition();
                            rulesPic[i].sprite.setPosition(*new Vector2f(pos.x, pos.y + 20));
                        }
                    }
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



void tests(RenderWindow& app, Music& music, int type) {
    Object bg = *new Object("src\\bg\\bg3.jpg", *new Vector2f(0, 0));
    Object rightArrow = *new Object("src\\buttons\\rightArrow.png", *new Vector2f(750, 850));
    Object leftArrow = *new Object("src\\buttons\\leftArrow.png", *new Vector2f(50, 850));
    sf::Vector2f textPosition(10, 10);
    sf::Vector2f scrollPosition(0, 0);
    float scrollSpeed = 20.0f;
    vector<test> tests;
    getNumTests(tests, type);
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
                    if (index == 10) { // TODO при последнем вопросе сделать окно
                        showResults(app, tests, music);
                        return;
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


void getNumTests(vector<test>& tests, int type) {
    int questNum = 14;
    if (type == 1)
        questNum = 13;
    srand(time(NULL));
    vector<int> nums;
    bool fl = false;
    int tempT = type;
    for (int i = 0; i < 10; ++i) {
        int temp = 1 + rand() % questNum;
        for (int j = 0; j < nums.size(); ++j) {
            if (nums[j] == temp) {
                fl = true; break;
            }
        }
        if (fl) {
            --i; fl = false; continue;
        }
        if (type == 3) {
            tempT = 1 + rand() % 3;
            --tempT;
        }
        nums.push_back(temp);
        tests.push_back(*new test(temp, tempT));
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


void showResults(RenderWindow& app, vector<test>& tests, Music& music) {
    int count = 0;
    Font font;
    font.loadFromFile("src\\Gagalin-Regular.otf");
    
    for (int i = 0; i < tests.size(); ++i) {
        if (tests[i].state)
            ++count;
    }
    Object bg = *new Object("src\\bg\\bg3.jpg", *new Vector2f(0, 0));
    

    while (app.isOpen())
    {
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                app.close();
           

        }

        Text temp(L"Выйти в главное меню", font, 82);
        temp.setPosition(75, 400);
        temp.setFillColor(Color::Black);
        selfText menu(temp);
        app.clear();
        app.draw(bg.sprite);

        if (isMouseOver(app, menu)) {
            Vector2f pos = menu.text.getPosition();
            menu.text.setScale(1.05f, 1.05f);
            menu.text.setPosition(pos.x - 15, pos.y - 2);
            menu.text.setFillColor(Color::Blue);
        }

        if (Mouse::isButtonPressed(Mouse::Left)) {
            if (isMouseOver(app, menu)) {
                mainMenu(app, music);
            }
        }
        app.draw(menu.text);
        
        Text text1(L"Ваш результат: ", font, 72);
        text1.setPosition(100, 300);
        text1.setFillColor(Color::Black);
        app.draw(text1);
        Text text2(to_string(count), font, 72);
        text2.setPosition(700, 300);
        text2.setFillColor(Color::Black);
        app.draw(text2);
        Text text3("/ 10 ", font, 72);
        text3.setPosition(760, 300);
        text3.setFillColor(Color::Black);
        app.draw(text3);
        app.display();
    }

}