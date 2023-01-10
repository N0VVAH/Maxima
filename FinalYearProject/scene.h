#pragma once
#include "sprite.h"


class scene
{
public:
	scene() {};
	virtual void update(sf::RenderWindow* window, float dtime) = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states);
	virtual char inputHandler() = 0;
	virtual void exitScene() = 0;
	virtual void closeScene() = 0;
	virtual void loadScene(scene*) = 0;

protected:
	std::vector<sprite*> render;
	std::vector<sprite*> UI;

	sf::Vector2i mouseDownPos;
	sf::Vector2i mouseUpPos;

	scene* prevScene;


};