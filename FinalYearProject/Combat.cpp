#include "combat.h"

combat::combat(scene* prev)
{
	prevScene = prev;

	background = Square(sf::Color::Magenta, 1600, 800);
	background.setPos(800, 400);
	render.push_back(&background);

	chara = Square(sf::Color::Green, 40, 100);
	chara.setPos(100, 200);
	render.push_back(&chara);


	enemy = Square(sf::Color::Red, 40, 100);
	enemy.setPos(600, 200);
	render.push_back(&enemy);
}

void combat::update(sf::RenderWindow* window, float dtime)
{

}

char combat::inputHandler()
{
	return 0;
}

void combat::exitScene()
{

}

void combat::closeScene()
{

}

void combat::loadScene(scene*)
{

}
