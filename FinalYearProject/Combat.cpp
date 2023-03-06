#include "combat.h"
#include "buttonSprite.h"
#include "buttonfuncs.h"
#include <iostream>
#include <string>


combat::combat(scene* prev)
{
	prevScene = prev;
	render.reserve(16);
	UI.reserve(32);
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

	textProps p;
	p.col = sf::Color::Black;
	p.fontSize = 30;
	p.string = Global::Player->name;

	Text* name = new Text(p);
	name->setPos(300, 120);
	render.push_back(name);

	enemy = Square(sf::Color::Red, 40, 100);
	enemy.setPos(1300, 200);
	render.push_back(&enemy);

	p.string = e.name;
	Text* Ename = new Text(p);
	Ename->setPos(1300, 120);
	render.push_back(Ename);

	//Combat History / Chat box
	Square* temp = new Square(sf::Color::Black, 400, 300);
	temp->setPos(200, 650);
	render.push_back(temp);



	p.col = sf::Color::White;
	p.fontSize = 24;
	p.string = "History";

	Text* HistoryTitle = new Text(p);
	HistoryTitle->setPos(200, 520);
	UI.push_back(HistoryTitle);


	//Stats
	std::string toSet;
	toSet.append("Health   : ");
	toSet.append(std::to_string(Global::Player->health));
	toSet.append("\nStamina : ");
	toSet.append(std::to_string(Global::Player->stamina));
	p.string = toSet.c_str();;

	PlayerStats = new Text(p);
	PlayerStats->setPos(300, 280);

	toSet.clear();
	toSet.append("Health   : ");
	toSet.append(std::to_string(e.health));
	toSet.append("\nStamina : ");
	toSet.append(std::to_string(e.stamina));
	p.string = toSet.c_str();

	EnemyStats = new Text(p);
	EnemyStats->setPos(1300, 280);

	UI.push_back(PlayerStats);
	UI.push_back(EnemyStats);

	//menu
	rightMove = Square(sf::Color::Black, 50, 25);
	rightMove.setPos(1445, 705);
	rightMove.type = ' ';
	
	leftMove = Square(sf::Color::Black, 50, 25);
	leftMove.setPos(1375, 705);
	leftMove.type = ' ';
	
	menu[0] = new buttonSprite(200, 70, sf::Color::Black);
	menu[0]->setPos(1100, 500);
	menu[0]->type = 'f';
	menu[0]->setClick(&Fight);
	UI.push_back(menu[0]);

	menu[1] = new buttonSprite(200, 70, sf::Color::Black);
	menu[1]->setPos(1350, 500);
	menu[1]->type = 'f';
	menu[1]->setClick(&Block);
	UI.push_back(menu[1]);

	menu[2] = new buttonSprite(200, 70, sf::Color::Black);
	menu[2]->setPos(1100, 610);
	menu[2]->type = 'f';
	menu[2]->setClick(&Inv);
	UI.push_back(menu[2]);

	menu[3] = new buttonSprite(200, 70, sf::Color::Black);
	menu[3]->setPos(1350, 610);
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
				switch (curDisplayed)
				{
				case 'F':
					for (size_t i = 0; i < moves.size(); i++)
					{
						removeFromUI(moves[i]);
					}
					removeFromUI(&rightMove);
					removeFromUI(&leftMove);
					for (size_t i = 0; i < 10; i++)
					{
						if (menu[i] != nullptr)
						{
							UI.push_back(menu[i]);
						}
						
					}
					curDisplayed = 'n';
					break;

				case 'n':
					break;

				default:
					break;
				}

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
							else if (UI[i]->type == 'M')
							{
								move* clickedMove = MoveController::getMove((uint32_t)UI[i]->getData());
								//std::cout << clickedMove->name << "\n";
								moveSelected(clickedMove);
							}
							else if (UI[i]->type == 'n')
							{
								((void(*)())UI[i]->onClick())();
							}
							else if (UI[i]->type == ' ')
							{
								std::cout << "Nothing\n";
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
		if (curDisplayed == 'F')
		{
			return;
		}
		curDisplayed = 'F';
		moveCount = Global::Player->moves.size();
		start = 0;
		if (moveCount > 10) { moveCount = 10; }
		moves.clear();

		for (size_t i = start; i < moveCount; i++)
		{
			moves.push_back(new Square(sf::Color::Black, 100, 35));
			if (i % 2 == 0)
			{
				moves[i]->setPos(1300, 500 + ((i / 2) * 50));
			}
			else
			{
				moves[i]->setPos(1420, 500 + ((i / 2) * 50));
			}
			moves[i]->setData((void*)Global::Player->moves[i]->id);
			moves[i]->type = 'M';
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

void combat::moveSelected(move* playerMove)
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
