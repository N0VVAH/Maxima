#include "mainmenu.h"
#include <iostream>
#include "buttonSprite.h"
#include "buttonfuncs.h"


MainMenu::MainMenu()
{
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
	render.push_back(Title);



	//UI.push_back(new buttonSprite(100, 100, "E:\\Files\\UNI year 3 Work\\Final Year Project\\Maxima\\x64\\Debug\\Sprites\\lol.png"));
	//UI[0]->setPos(200, 200);
}


void MainMenu::update(sf::RenderWindow* window, float dtime)
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

