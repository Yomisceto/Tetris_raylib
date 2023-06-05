#include "TextBox.h"


TextBox::TextBox(Vec2<int> position, const std::string& text, int fontSize, Color color)
	: 
	text(text),
	color(color),
	fontSize(fontSize),
	position(position)
{
}

void TextBox::Draw()
{
	if (isVisible)
	{
		DrawText(TextFormat(text.c_str()),
			position.GetX(),
			position.GetY(),
			fontSize, 
			color);
	}
}
