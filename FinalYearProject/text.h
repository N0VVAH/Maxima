#pragma once
#include "sprite.h"



struct textProps 
{
	sf::Color col = sf::Color::Black;
	float fontSize = 30;
	const char* string = "Temp";
	char origin = 'c';
};


class Text : public sprite
{
public:
	Text() 
	{
		init();
	}
	Text(textProps p);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void* onClick() override;
	virtual void setClick(void*) override;
	virtual void setPos(float xPos, float yPos) override;
	virtual void movePos(float xOffset, float yOffset) override;
	virtual inline void changeText(const char* t) override { props.string = t; text.setString(t); }

	void init();
	void updateText(const char* te);

protected:
	textProps props;
	sf::Font font;
	sf::Text text;
};