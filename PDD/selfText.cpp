#include "selfText.h"

selfText::selfText(Text text)
{
	this->text = text;
	bounds = text.getLocalBounds();
}
