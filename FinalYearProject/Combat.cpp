#include "combat.h"
#include "buttonSprite.h"
#include "buttonfuncs.h"
#include <iostream>

combat::combat(scene* prev)
{
	prevScene = prev;
	render.reserve(16);
	moves.reserve(Global::Player->moves.size() * 2);

	Global::Player->moves.push_back(new move());
	Global::Player->moves.push_back(new move());
	Global::Player->moves.push_back(new move());
	Global::Player->moves.push_back(new move());
	Global::Player->moves.push_back(new move());


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
	rightMove = Square(sf::Color::Black, 50, 25);
	rightMove.setPos(1245, 705);
	//render.push_back(&rightMove);

	leftMove = Square(sf::Color::Black, 50, 25);
	leftMove.setPos(1175, 705);
	//render.push_back(&leftMove);


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
								changeButtons(todo);
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

void combat::changeButtons(char butt)
{
	for (size_t i = 0; i < 10; i++)
	{
		if (menu[i] != nullptr)
		{
			removeFromUI(menu[i]);
		}
	}

	int moveCount;
	int start;
	switch (butt)
	{
	case 'F':
		moveCount = Global::Player->moves.size();
		start = 0;
		if (moveCount > 10) { moveCount = 10; }

		for (size_t i = start; i < moveCount; i++)
		{
			if (i % 2 == 0)
			{
				moves.push_back(new Square(sf::Color::Black, 100, 35));
				moves[i]->setPos(1100, 500 + ((i / 2) * 50));
				UI.push_back(moves[i]);
			}
			else
			{
				moves.push_back(new Square(sf::Color::Black, 100, 35));
				moves[i]->setPos(1220, 500 + ((i / 2) * 50));
				UI.push_back(moves[i]);
			}
			UI.push_back(&leftMove);
			UI.push_back(&rightMove);
			if (moveCount == 10 && (start + 10) < Global::Player->moves.size())
			{
				rightMove.setFillColour(sf::Color::Black);
			}
			else
			{
				rightMove.setFillColour(sf::Color::White);
			}
			if (start != 0)
			{
				leftMove.setFillColour(sf::Color::Black);
			}
			else
			{
				leftMove.setFillColour(sf::Color::White);
			}

		}

		return;

	case 'b':

		return;

	case 'i':

		return;

	case 'f':

		return;

	case 'm':
		for (size_t i = 0; i < sizeof(menu) / sizeof(sprite*); i++)
		{
			if (menu[i] != nullptr)
			{

				render.push_back(menu[i]);
			}
		}
		break;

	default:
		break;
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
