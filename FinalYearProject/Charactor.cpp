#include "Charactor.h"
#include "iostream"

void Charactor::CharSetup(const char* path)
{
	chara = new sf::RectangleShape();
	try
	{
		texture.loadFromFile(path);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
	}

	chara->setSize({ 50, 50 });
	chara->setTexture(&texture);
	lastpos = sf::Vector2f{ 50, 50 };
}

void Charactor::CharSetup(sf::Color colour)
{
	chara = new sf::RectangleShape();
	chara->setSize({ 50, 50 });
	chara->setFillColor(colour);
	lastpos = sf::Vector2f{ 50, 50 };
}

void Charactor::CharSetup(sf::Color colour, float x, float y)
{
	chara = new sf::RectangleShape();
	chara->setSize({ x, y });
	chara->setFillColor(colour);
	lastpos = sf::Vector2f{ 50, 50 };
}

void Charactor::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*chara, states);
}

void* Charactor::onClick()
{
	return nullptr;
}

void Charactor::setClick(void*)
{

}

void Charactor::setPos(float xPos, float yPos)
{
	chara->setPosition({ xPos, yPos });
	lastpos = sf::Vector2f{ xPos, yPos };
}

void Charactor::movePos(float xOffset, float yOffset)
{
	lastpos = chara->getPosition();
	chara->move({ xOffset, yOffset });
}
