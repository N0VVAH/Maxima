#pragma once
#include "sprite.h"

class Square : public sprite
{
public:
	Square() {}
	Square(sf::Color, int xSize, int ySize);
	Square(sf::Color);
	Square(const char* path);
	Square(const char* path, int xSize, int ySize);
	Square(const char* path, sf::IntRect);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void update(float timestep) override;
	virtual void* onClick();
	virtual void setClick(void*);
	virtual void setPos(float xPos, float yPos);
	virtual void movePos(float xOffset, float yOffset);
	void changeMapping(sf::IntRect);
	virtual void setSize(float xOffset, float yOffset) override;
	inline sf::FloatRect getLocalBounds() override { return shape.getLocalBounds(); }
	inline sf::FloatRect getGlobalBounds() override { return shape.getGlobalBounds(); }
	virtual inline void setFillColour(sf::Color colour) override { shape.setFillColor(colour); }
	inline virtual sf::Vector2f getPos() override { return shape.getPosition(); }
	void updateTexture() override;


private:
	sf::RectangleShape shape;


};