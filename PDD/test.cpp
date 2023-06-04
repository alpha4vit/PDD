
#include "test.h"
vector<selfText> mixAnswers(vector<selfText> vec);
test::test(int number)
{
	this->task = *new Object("src\\tests\\" + to_string(number) + "\\task.png", *new Vector2f(100, 100));

	int x = 100;
	int y = 500;
	Font font;
	font.loadFromFile("src\\Gagalin-Regular.otf");
	fstream file;
	file.imbue(std::locale(""));
	file.open("src\\tests\\" + to_string(number) + "\\answers.txt");
	vector<selfText> tempVec;
	for (int i = 0; i < 4; ++i) {
		string temp;
		getline(file, temp);
		if (i == 0) {
			this->correctAnswer = sf::String::fromUtf8(temp.begin(), temp.end()); continue;
		}
		Text textTemp(sf::String::fromUtf8(temp.begin(), temp.end()), font, 22);
		textTemp.setFillColor(Color::Black);
		textTemp.setPosition(*new Vector2f(x, y));
		y += 35;
		this->answers.push_back(selfText(textTemp));
	}
	this->state = false;
}
