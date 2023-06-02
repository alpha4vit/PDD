#pragma once
#include"includes.h"
class image
{
public:
	Image img;
	Texture texture;
	Sprite sprite;

	image(int captureNum, int picNum, Vector2f pos, int type);
	void setPosition(Vector2f pos);
};

void fillVector(int captureNum, vector<image>& vec, int type);
