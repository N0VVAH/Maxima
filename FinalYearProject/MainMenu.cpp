#include "mainmenu.h"
#include <iostream>
#include "buttonSprite.h"


MainMenu::MainMenu()
{

	UI.push_back(new buttonSprite(100, 100, "E:\\Files\\UNI year 3 Work\\Final Year Project\\Maxima\\x64\\Debug\\Sprites\\lol.png"));
	UI[0]->setPos(200, 200);
}


void MainMenu::update(sf::RenderWindow* window)
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
					if (UI[0]->getGlobalBounds().contains(mouseDownPos.x, mouseDownPos.y) && UI[0]->getGlobalBounds().contains(mouseUpPos.x, mouseUpPos.y))
					{
						UI[0]->onClick();
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

void MainMenu::draw(sf::RenderTarget& target, sf::RenderStates states)
{

	for (size_t i = 0; i < render.size(); i++)
	{
		render[i]->draw(target, states);
	}

	for (size_t i = 0; i < UI.size(); i++)
	{
		UI[i]->draw(target, states);
	}
	
}

