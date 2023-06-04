#pragma once
#include"includes.h"
#include"Object.h"
#include"selfText.h"
class test
{
public:
	Object task;
	vector<selfText> answers;
	sf::String correctAnswer;
	bool state;
	test(int number);
};
