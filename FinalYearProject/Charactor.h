#pragma once
#include "sprite.h"

class Charactor : public sprite
{
public:
	Charactor() {}
	void CharSetup(const char* path);
	void CharSetup(sf::Color colour);
	void CharSetup(sf::Color colour, float x, float y);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void* onClick() override;
	virtual void setClick(void*) override;
	virtual void setPos(float xPos, float yPos) override;
	virtual void movePos(float xOffset, float yOffset) override;
	inline sf::FloatRect getLocalBounds() override { return chara->getLocalBounds(); }
	inline sf::FloatRect getGlobalBounds() override { return chara->getGlobalBounds(); }

private:
	sf::RectangleShape* chara;
	sf::Texture texture;
	sf::Vector2f lastpos;
};
