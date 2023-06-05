#pragma once
#include "Vec2.h"
#include <string>
#include "raylibCpp.h"

/** Simple Text displayer, user can easily create it and draw on screen. */
class TextBox
{
public:
	virtual ~TextBox() = default;

	TextBox(Vec2<int> position, const std::string& text, int fontSize, Color color);

	virtual void Draw();

	/** Currently this functions is not used */
	void Show() { isVisible = true; }
	void Hide() { isVisible = false; }

protected:
	std::string getText() const { return text; }
	Vec2<int> getPosition() const { return position; }
	Color getColor() const { return color; }
	int getFontSize() const { return fontSize; }
	bool getVisibility() const { return isVisible; }

private:
	std::string text;
	Color color;
	int fontSize;
	Vec2<int> position;
	bool isVisible = true;


};

/** Text box that can change value.
 *  String should be C style value print. */
template <typename T> 
class ValueDisplayer : public TextBox
{
public:
	ValueDisplayer(Vec2<int> position, const std::string& text,
		int fontSize, Color color, T* value);

	void Draw() override;

private:
	T* value;
};

template <typename T>
ValueDisplayer<T>::ValueDisplayer(Vec2<int> position, const std::string& text,
	int fontSize, Color color, T* value)
	: TextBox(position, text, fontSize, color),
	value(value)
{

}

template<typename T>
void ValueDisplayer<T>::Draw()
{
	if (getVisibility() && value)
	{
		DrawText(TextFormat(getText().c_str(), *value),
			getPosition().GetX(), getPosition().GetY(), getFontSize(), getColor());
	}
}
