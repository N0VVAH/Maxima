#include "buttonSprite.h"
#include "iostream"

buttonSprite::buttonSprite()
{

}

buttonSprite::buttonSprite(float width, float height, sf::Color colour)
{
	shape = new sf::RectangleShape(sf::Vector2f(width, height));
	shape->setFillColor(colour);
}

buttonSprite::buttonSprite(float width, float height, std::string path)
{
	shape = new sf::RectangleShape(sf::Vector2f(width, height));
	if (!texture->loadFromFile(path)) { }
	texture->setSmooth(true);

	shape->setTexture(texture);
}

void buttonSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw((*shape), states);
}

void buttonSprite::onClick()
{
	std::cout << "Working\n";
}

void buttonSprite::setPos(float xPos, float yPos)
{
	shape->setPosition(sf::Vector2f(xPos, yPos));
}

sf::FloatRect buttonSprite::getLocalBounds()
{
	return shape->getLocalBounds();
}

sf::FloatRect buttonSprite::getGlobalBounds()
{
	return shape->getGlobalBounds();
}