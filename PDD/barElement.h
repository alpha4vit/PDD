#pragma once
#include"includes.h"
class barElement
{
public:
	RectangleShape rect;
	Text number;
	barElement(int number, int x, int y);

	bool isMouseOver(RenderWindow& window);
};

