#pragma once
#include "sprite.h"

class Square : public sprite
{
public:
	Square() {}
	Square(sf::Color, int xSize, int ySize);
	Square(sf::Color);
	Square(const char* path);
	Square(const char* path, sf::IntRect);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void* onClick();
	virtual void setClick(void*);
	virtual void setPos(float xPos, float yPos);
	virtual void movePos(float xOffset, float yOffset);
	void changeMapping(sf::IntRect);

private:
	sf::RectangleShape shape;


};