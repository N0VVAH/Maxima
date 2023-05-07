#include "playerdeath.h"
#include "buttonSprite.h"
#include "text.h"
#include "globals.h"
#include "buttonfuncs.h"

PlayerDeath::PlayerDeath(scene* ls)
{
	prevScene = ls; 

	backGround.setPos(800, 400);

	quit = new buttonSprite(200, 75, sf::Color::Black);
	quit->setPos(800, 400);
	quit->setClick(&clickQuick);

	textProps p;
	p.col = sf::Color::White;
	p.fontSize = 24;
	p.string = "Quit Game";

	quitText = new Text(p);
	quitText->setPos(800, 400);

	p.string = "You Have Died...";
	p.col = sf::Color::Black;
	p.fontSize = 36;
	title = new Text(p);
	title->setPos(800, 200);

	p.fontSize = 24;
	p.col = sf::Color::White;
	loadLastSave = new buttonSprite(200, 75, sf::Color::Black);
	loadLastSave->setPos(800, 600);
	loadLastSave->setClick(&loadMainMenu);

	p.string = "Play Again";
	loadText = new Text(p);
	loadText->setPos(800, 600);


	render.push_back(&backGround);

	UI.push_back(title);
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
				mouseDownPos = { events->mouseButton.x, events->mouseButton.y };
			}

			break;

		case sf::Event::MouseButtonReleased:
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == false && mouseDownPos != sf::Vector2i())
			{

				mouseUpPos = { events->mouseButton.x, events->mouseButton.y };
				for (size_t i = 0; i < UI.size(); i++)
				{
					if (UI[i]->getGlobalBounds().contains(mouseDownPos.x, mouseDownPos.y) && UI[i]->getGlobalBounds().contains(mouseUpPos.x, mouseUpPos.y))
					{
						if (UI[i]->type == 'S')
						{
							loadScene(((scene * (*)())UI[i]->onClick())());
						}
						else
						{
							((void(*)())UI[i]->onClick())();
							delete prevScene;
							return;
						}

					}
				}

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
	closeScene();
	Global::curScene = prevScene;
}

void PlayerDeath::closeScene()
{
	delete quit;
	delete quitText;
	delete loadLastSave;
	delete loadText;

}

void PlayerDeath::loadScene(scene*)
{
}
