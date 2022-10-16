#pragma once
#include <SFML/Graphics.hpp>

class sprite : public sf::Drawable
{
public:
	sprite() { } //default
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	virtual void onClick() = 0;
	virtual void setPos(float xPos, float yPos) = 0;
	inline virtual sf::FloatRect getLocalBounds() { return sf::FloatRect(); }
	inline virtual sf::FloatRect getGlobalBounds() { return sf::FloatRect(); }

protected:
	sf::Texture texture;
};