#include "mainmenu.h"
#include <iostream>
#include "buttonSprite.h"
#include "buttonfuncs.h"
#include <chrono>


MainMenu::MainMenu()
{
	background = new Square("..\\assets\\images\\backgrounds\\mainmenu.png", 3200, 3200);
	background->setPos(800, 400);
	render.push_back(background);

	player = new Square("..\\assets\\images\\playersingle.png", 128, 128);
	player->setPos(200, 200);
	render.push_back(player);


	UI.push_back(new buttonSprite(300, 100, sf::Color::White));
	UI[0]->setPos(800, 200);
	UI[0]->setClick(&clickStart);
	UI[0]->type = 'S';

	UI.push_back(new buttonSprite(300, 100, sf::Color::White));
	UI[1]->setPos(800, 600);
	UI[1]->setClick(&clickQuick);

	textProps p;
	p.col = sf::Color::White;
	p.string = "Maxima";
	p.fontSize = 50;

	Text* Title = new Text(p);
	Title->setPos(800, 50);

	p.col = sf::Color::Black;
	p.string = "Start";
	p.fontSize = 30;

	Text* Start = new Text(p);
	Start->setPos(800, 190);

	p.string = "Quit";

	Text* Quit = new Text(p);
	Quit->setPos(800, 590);

	UI.push_back(Start);
	UI.push_back(Quit);
	UI.push_back(Title);

	viewPos = sf::Vector2f(0.0f, 0.0f);

	yMovement = 19.47f;
	xMovement = 80.64f;
	std::srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());
}


void MainMenu::update(sf::RenderWindow* window, float dtime)
{
	sf::Event* events = new sf::Event;
	
	//randomly moves the camera
	if ((viewPos.x >= 800 && xMovement >= 0.0f) || (viewPos.x <= -800 && xMovement <= 0.0f))
	{
		xMovement += ((std::rand() % 200) - 100) / 100;
		xMovement *= -1;
	}
	if ((viewPos.y >= 1000 && yMovement >= 0.0f) || (viewPos.y <= -800 && yMovement <= 0.0f))
	{
		yMovement += ((std::rand() % 200) - 100) / 100;
		yMovement *= -1;
	}

	sf::Vector2f frameMovement = sf::Vector2f(xMovement * dtime, yMovement * dtime);
	viewPos += frameMovement;
	Global::mainView->move(frameMovement);
	Global::updateView = true;

	for (size_t i = 0; i < UI.size(); i++)
	{
		UI[i]->movePos(frameMovement.x, frameMovement.y);
	}


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
					if (UI[i]->getGlobalBounds().contains(mouseDownPos.x + viewPos.x, mouseDownPos.y + viewPos.y) && UI[i]->getGlobalBounds().contains(mouseUpPos.x + viewPos.x, mouseUpPos.y + viewPos.y))
					{
						if (UI[i]->type == 'S')
						{
							loadScene(((scene * (*)())UI[i]->onClick())());
						}
						else
						{
							((void(*)())UI[i]->onClick())();
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

char MainMenu::inputHandler()
{
	return '0';
}


void MainMenu::loadScene(scene* nextScene)
{
	prevScene = this;
	Global::curScene = nextScene;
}

void MainMenu::exitScene()
{
	Global::window->close();
}

void MainMenu::closeScene()
{
	Global::window->close();
}

