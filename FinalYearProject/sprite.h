#pragma once
#include <SFML/Graphics.hpp>
#include <functional>


class sprite : public sf::Drawable
{
public:
	sprite() { } //default
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	virtual void* onClick() = 0;
	virtual void setClick(void*) = 0;
	inline virtual void setData(void* d) { data = d; }
	inline virtual void* getData() { return data; }
	virtual void setPos(float xPos, float yPos) = 0;
	virtual void movePos(float xOffset, float yOffset) = 0;
	inline virtual sf::FloatRect getLocalBounds() { return sf::FloatRect(); }
	inline virtual sf::FloatRect getGlobalBounds() { return sf::FloatRect(); }
	inline virtual void changeText(const char* text) {}
	virtual void setFillColour(sf::Color colour) {};
	inline virtual sf::Vector2f getPos() { return sf::Vector2f(0.0f, 0.0f); }
	char type;

protected:
	void* data;
	sf::Texture texture;
	void (*Click)(void);
};