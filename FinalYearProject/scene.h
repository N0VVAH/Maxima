#pragma once

#include "sprite.h"

class scene
{
public:
	scene() {};
	virtual void update(sf::RenderWindow* window) = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) = 0;
	virtual char inputHandler() = 0;



protected:
	std::vector<sprite*> render;
	std::vector<sprite*> UI;

	sf::Vector2<int> mouseDownPos;


private:

};