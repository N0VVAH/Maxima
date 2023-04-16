#include "text.h"
#include <iostream>

Text::Text(textProps p)
{

	props = p;
	init();
}

void Text::init()
{
	if (!font.loadFromFile("..\\assets\\fonts\\qazsans.ttf"))
	{
		std::cout << "FAILED TO LOAD FONT\n";
	}

	text.setFont(font);

	text.setString(props.string);

	text.setCharacterSize(props.fontSize);

	text.setFillColor(props.col);

	if (props.origin == 'c')
	{
		text.setOrigin(sf::Vector2f(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2));
	}
	else if (props.origin == 'b')
	{
		text.setOrigin(sf::Vector2f(0, text.getGlobalBounds().height));
	}
	
}

void Text::updateText(const char* te)
{
	text.setString(te);
}


void Text::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(text, states);
}

void* Text::onClick()
{
	return nullptr;
}

void Text::setClick(void*)
{

}

void Text::setPos(float xPos, float yPos)
{
	text.setPosition(sf::Vector2f(xPos, yPos));
}

void Text::movePos(float xOffset, float yOffset)
{
	text.move(sf::Vector2f(xOffset, yOffset));
}


