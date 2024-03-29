#pragma once
#include "sprite.h"
#include <string>

class buttonSprite : public sprite
{
public:
	buttonSprite();
	buttonSprite(float width, float height, sf::Color colour);
	buttonSprite(float width, float height, std::string path);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void* onClick() override;
	virtual void setClick(void*) override;
	virtual void setPos(float xPos, float yPos) override;
	virtual void movePos(float xOffset, float yOffset) override;
	sf::FloatRect getLocalBounds() override;
	sf::FloatRect getGlobalBounds() override;
	char type;

private:
	sf::RectangleShape shape;
};