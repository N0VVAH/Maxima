#pragma once
#include <SFML/Graphics.hpp>

class sprite : public sf::Drawable
{
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) = 0;
	virtual void onClick() = 0;
};