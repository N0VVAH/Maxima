#include "combat.h"
#include "buttonSprite.h"
#include "buttonfuncs.h"
#include <iostream>

combat::combat(scene* prev)
{
	prevScene = prev;

	//main none changing of battle UI

	background = Square(sf::Color::Magenta, 1600, 800);
	background.setPos(800, 400);
	render.push_back(&background);

	chara = Square(sf::Color::Green, 40, 100);
	chara.setPos(300, 200);
	render.push_back(&chara);


	enemy = Square(sf::Color::Red, 40, 100);
	enemy.setPos(1300, 200);
	render.push_back(&enemy);

	//menu
	menu[0] = new buttonSprite(200, 70, sf::Color::Black);
	menu[0]->setPos(900, 500);
	menu[0]->type = 'f';
	menu[0]->setClick(&Fight);
	UI.push_back(menu[0]);

	menu[1] = new buttonSprite(200, 70, sf::Color::Black);
	menu[1]->setPos(1150, 500);
	menu[1]->type = 'f';
	menu[1]->setClick(&Block);
	UI.push_back(menu[1]);

	menu[2] = new buttonSprite(200, 70, sf::Color::Black);
	menu[2]->setPos(900, 610);
	menu[2]->type = 'f';
	menu[2]->setClick(&Inv);
	UI.push_back(menu[2]);

	menu[3] = new buttonSprite(200, 70, sf::Color::Black);
	menu[3]->setPos(1150, 610);
	menu[3]->type = 'f';
	menu[3]->setClick(&Flee);
	UI.push_back(menu[3]);
}

void combat::update(sf::RenderWindow* window, float dtime)
{
	sf::Event* events = new sf::Event;
	while (window->pollEvent(*events))
	{
		switch ((*events).type)
		{

		case sf::Event::KeyPressed:
			switch ((*events).key.code)
			{
			case sf::Keyboard::Escape:
				exitScene();
				break;

			default:
				break;
			}
			break;


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
							else if (UI[i]->type == 'f')
							{
								char todo = ((char(*)())UI[i]->onClick())();
								std::cout << todo << "\n";
								switch (todo)
								{
								case 'F':

									break;

								case 'b':

									break;

								case 'i':

									break;

								case 'f':

									break;
								default:
									break;
								}
							}
							else
							{
								((void(*)())UI[i]->onClick())();
							}

						}
					}

					mouseDownPos = sf::Vector2i();
				}
			}

		default:
			break;
		}
	}
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
