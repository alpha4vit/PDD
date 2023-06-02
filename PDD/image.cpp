#include "image.h"
//
//
//
//
// TODO сделать скрины для 25 главы
//
//
//
//
image::image(int captureNum, int picNum, Vector2f pos, int type)
{
	this->img = Image();
	if (type == 0 && !this->img.loadFromFile("src\\captures\\" + to_string(captureNum) + "\\" + to_string(picNum) + ".png")) {
		exit(-1);
	}
	else if ((type == 1 && !this->img.loadFromFile("src\\signs\\" + to_string(captureNum) + "\\" + to_string(picNum) + ".png"))) {
		exit(-1);
	}
	this->texture = Texture();
	this->texture.loadFromImage(this->img);
	this->sprite = Sprite();
	this->sprite.setTexture(this->texture);
	this->sprite.setPosition(pos);

}

void image::setPosition(Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void fillVector(int captureNum, vector<image>& vec, int type)
{
	if (type == 0) {
		int y = 20;
		if (captureNum < 8) ++captureNum;
		if (captureNum > 14) --captureNum;
		if (captureNum > 22) --captureNum;
		if (captureNum > 26) --captureNum;
		if (captureNum > 27) --captureNum;
		if (captureNum - 1 == 0) {
			for (int i = 1; i <= 7; ++i) {
				vec.push_back(*new image(captureNum, i, *new Vector2f(40, y), 0));
				if (i == 1) y += 510;
				else if (i == 2) y += 588;
				else if (i == 3) y += 1239;
				else if (i == 4 || i == 5) y += 1278;
				else if (i == 6) y += 1305;
			}
		}
		else if (captureNum - 1 == 1 || captureNum - 1 == 4 || captureNum - 1 == 7 || captureNum == 8 || captureNum == 11 || captureNum == 12 || captureNum == 14 || captureNum == 15 || captureNum == 16 || captureNum == 17 || captureNum == 18 || captureNum == 21 || captureNum == 27 || captureNum == 25) {
			vec.push_back(*new image(captureNum, 1, *new Vector2f(40, 20), 0));
		}
		else if (captureNum - 1 == 2) {
			for (int i = 1; i <= 4; ++i) {
				vec.push_back(*new image(captureNum, i, *new Vector2f(40, y), 0));
				y += 1318;
			}
		}
		else if (captureNum - 1 == 3 || captureNum == 9 || captureNum == 10 || captureNum == 13 || captureNum == 19 || captureNum == 20 || captureNum == 22 || captureNum == 23 || captureNum == 24) {
			for (int i = 1; i <= 2; ++i) {
				vec.push_back(*new image(captureNum, i, *new Vector2f(40, y), 0));
				y += 1318;
			}
		}
		else if (captureNum - 1 == 5 || captureNum - 1 == 6 || captureNum == 26) {
			for (int i = 1; i <= 3; ++i) {
				vec.push_back(*new image(captureNum, i, *new Vector2f(40, y), 0));
				y += 1319;
			}
		}
	}
	else if (type == 1) {
		int y = 20;
		for (int i = 0; i < 8; ++i) {
			if (captureNum == 1)
				vec.push_back(*new image(captureNum, 1, *new Vector2f(40, y), 1));
			else if (captureNum == 2 || captureNum == 4) {
				for (int i = 1; i <= 6; ++i) {
					vec.push_back(*new image(captureNum, 1, *new Vector2f(40, y), 1));
					y += 1308;
				}
			}
			else if (captureNum == 3) {
				for (int i = 1; i <= 6; ++i) {
					vec.push_back(*new image(captureNum, 1, *new Vector2f(40, y), 1));
					y += 1308;
				}
			}
			else if (captureNum == 5 || captureNum == 7) {
				for (int i = 1; i <= 3; ++i) {
					vec.push_back(*new image(captureNum, 1, *new Vector2f(40, y), 1));
					y += 1308;
				}
			}
			else if (captureNum == 6) {
				for (int i = 1; i <= 10; ++i) {
					vec.push_back(*new image(captureNum, 1, *new Vector2f(40, y), 1));
					y += 1308;
				}
			}
			else if (captureNum == 8) {
				for (int i = 1; i <= 4; ++i) {
					vec.push_back(*new image(captureNum, 1, *new Vector2f(40, y), 1));
					y += 1308;
				}
			}
		}
	}

}