#include "fightwon.h"

FightWon::FightWon(scene* prev)
{
	prevScene = prev;
}

void FightWon::update(sf::RenderWindow* window, float dtime)
{
	sf::Event* events = new sf::Event;

	while (window->pollEvent(*events))
	{
		switch ((*events).type)
		{
		case sf::Event::Closed:
			(*window).close();
			break;

		case sf::Event::MouseButtonPressed:
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				mouseDownPos = sf::Mouse::getPosition();
			}

			break;

		case sf::Event::MouseButtonReleased:
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == false && mouseDownPos != sf::Vector2i())
			{
				mouseDownPos = sf::Vector2i();
			}

		default:
			break;
		}
	}
}

char FightWon::inputHandler()
{
	return 0;
}

void FightWon::exitScene()
{

}

void FightWon::closeScene()
{

}

void FightWon::loadScene(scene*)
{

}
