#include "playerdeath.h"
#include "buttonSprite.h"
#include "text.h"
#include "globals.h"

PlayerDeath::PlayerDeath(scene* ls)
{
	prevScene = ls; 

	backGround.setPos(800, 400);

	quit = new buttonSprite(200, 75, sf::Color::Black);
	quit->setPos(800, 300);

	textProps p;
	p.col = sf::Color::White;
	p.fontSize = 24;
	p.string = "Quit Game";

	quitText = new Text(p);
	quitText->setPos(800, 300);

	loadLastSave = new buttonSprite(200, 75, sf::Color::Black);
	loadLastSave->setPos(800, 500);

	p.string = "Load Save";
	loadText = new Text(p);
	loadText->setPos(800, 500);

	render.push_back(&backGround);

	UI.push_back(quit);
	UI.push_back(quitText);
	UI.push_back(loadLastSave);
	UI.push_back(loadText);

}

void PlayerDeath::update(sf::RenderWindow* window, float dtime)
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

char PlayerDeath::inputHandler()
{
	return 0;
}

void PlayerDeath::exitScene()
{
}

void PlayerDeath::closeScene()
{
	delete quit;
	delete quitText;
	delete loadLastSave;
	delete loadText;
	Global::curScene = prevScene;
}

void PlayerDeath::loadScene(scene*)
{
}
