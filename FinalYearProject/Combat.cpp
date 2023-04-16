#include "combat.h"
#include "buttonSprite.h"
#include "buttonfuncs.h"
#include <iostream>
#include <string>
#include <chrono>
#include "playerdeath.h"
#include "fightwon.h"

combat::combat(scene* prev, int* done, Enemy en)
{
	e = en;
	doneFight = done;

	prevScene = prev;
	render.reserve(16);
	UI.reserve(32);
	moves.reserve(100);

	for (int i = 0; i < 10; i++)
	{
		history[i] = " ";
	}

	Global::Player->moves.push_back(MoveController::getMove(10));
	Global::Player->moves.push_back(MoveController::getMove(10));
	Global::Player->moves.push_back(MoveController::getMove(10));
	Global::Player->moves.push_back(MoveController::getMove(10));
	Global::Player->moves.push_back(MoveController::getMove(10));



	//main none changing of battle UI
	background = new Square("..\\assets\\images\\backgrounds\\comabt.png", 1600, 800);
	background->setPos(800, 400);
	render.push_back(background);

	playerCircle = new Square("..\\assets\\images\\icons\\battlecircle.png", 256, 128);
	playerCircle->setPos(1300, 250);
	render.push_back(playerCircle);

	enemyCircle = new Square("..\\assets\\images\\icons\\battlecircle.png", 256, 128);
	enemyCircle->setPos(300, 250);
	render.push_back(enemyCircle);


	chara = new Square("..\\assets\\images\\sidechar.png", 60, 150);
	textureAtlasProps a = textureAtlasProps();
	a.uvSize = sf::Vector2f(40, 100);
	a.timeBetween = 0.3;
	a.texturesInAtlas = 4;
	chara->setTextureAtlas(a);
	chara->updateTexture();
	chara->setPos(300, 180);
	render.push_back(chara);

	textProps p;
	p.col = sf::Color::Black;
	p.fontSize = 30;
	p.string = Global::Player->name;

	name = new Text(p);
	name->setPos(300, 100);
	render.push_back(name);

	enemy = new Square(e.texture, 40, 100);
	enemy->setPos(1300, 200);
	textureAtlasProps ta = textureAtlasProps();
	ta.timeBetween = 0.3;
	ta.texturesInAtlas = 5;
	enemy->setTextureAtlas(ta);
	enemy->updateTexture();
	render.push_back(enemy);

	p.string = e.name;
	Ename = new Text(p);
	Ename->setPos(1300, 100);
	render.push_back(Ename);

	//Combat History / Chat box
	Global::ChatBox->setSize(400, 300);
	Global::ChatBox->setPos(225, 575);
	render.push_back(Global::ChatBox);



	p.col = sf::Color::Black;
	p.fontSize = 24;
	p.string = "History";

	Text* HistoryTitle = new Text(p);
	HistoryTitle->setPos(200, 520);
	UI.push_back(HistoryTitle);

	p.fontSize = 16;
	p.origin = 'b';
	p.string = " ";
	historyText = new Text(p);
	historyText->setPos(10, 550);
	UI.push_back(historyText);

	p.origin = 'c';
	p.fontSize = 24;

	//Stats
	std::string toSet;
	toSet.append("Health   : ");
	toSet.append(std::to_string(Global::Player->health));
	toSet.append("\nStamina : ");
	toSet.append(std::to_string(Global::Player->stamina));
	p.string = toSet.c_str();
	p.col == sf::Color::White;

	PlayerStats = new Text(p);
	PlayerStats->setPos(300, 350);

	toSet.clear();
	toSet.append("Health   : ");
	toSet.append(std::to_string(e.health));
	toSet.append("\nStamina : ");
	toSet.append(std::to_string(e.stamina));
	p.string = toSet.c_str();

	EnemyStats = new Text(p);
	EnemyStats->setPos(1300, 350);

	UI.push_back(PlayerStats);
	UI.push_back(EnemyStats);

	//menu
	rightMove = Square(sf::Color::Black, 50, 25);
	rightMove.setPos(1445, 705);
	rightMove.type = ' ';
	
	leftMove = Square(sf::Color::Black, 50, 25);
	leftMove.setPos(1375, 705);
	leftMove.type = ' ';

	p.col = sf::Color::White;
	p.fontSize = 22;
	
	menu[0] = new buttonSprite(200, 70, sf::Color::Black);
	menu[0]->setPos(1100, 500);
	menu[0]->type = 'f';
	menu[0]->setClick(&Fight);
	p.string = "Fight";
	menu[4] = new Text(p);
	menu[4]->setPos(1100, 495);
	UI.push_back(menu[0]);
	UI.push_back(menu[4]);

	menu[1] = new buttonSprite(200, 70, sf::Color::Black);
	menu[1]->setPos(1350, 500);
	menu[1]->type = 'f';
	menu[1]->setClick(&Block);
	p.string = "Block";
	menu[5] = new Text(p);
	menu[5]->setPos(1350, 490);
	UI.push_back(menu[1]);
	UI.push_back(menu[5]);

	menu[2] = new buttonSprite(200, 70, sf::Color::Black);
	menu[2]->setPos(1100, 610);
	menu[2]->type = 'f';
	menu[2]->setClick(&Inv);
	p.string = "INV";
	menu[6] = new Text(p);
	menu[6]->setPos(1100, 600);
	UI.push_back(menu[2]);
	UI.push_back(menu[6]);

	menu[3] = new buttonSprite(200, 70, sf::Color::Black);
	menu[3]->setPos(1350, 610);
	menu[3]->type = 'f';
	menu[3]->setClick(&Flee);
	p.string = "Flee";
	menu[7] = new Text(p);
	menu[7]->setPos(1350, 600);
	UI.push_back(menu[3]);
	UI.push_back(menu[7]);

	PlayerDies = new PlayerDeath(prev);
	PlayerWins = new FightWon(prev, e);// , e);

}

void combat::update(sf::RenderWindow* window, float dtime)
{
	chara->update(dtime);
	enemy->update(dtime);

	sf::Event* events = new sf::Event;
	while (window->pollEvent(*events))
	{

		if (Global::curScene != this)
		{
			return;
		}

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
								break;
							}
							else if (UI[i]->type == 'f')
							{
								char todo = ((char(*)())UI[i]->onClick())();
								changeButtons(todo);
								break;
							}
							else if (UI[i]->type == 'M')
							{
								move* clickedMove = MoveController::getMove((uint32_t)UI[i]->getData());
								//std::cout << clickedMove->name << "\n";
								moveSelected(clickedMove);
								break;
							}
							else if (UI[i]->type == 'n')
							{
								((void(*)())UI[i]->onClick())();
								break;
							}
							else if (UI[i]->type == ' ')
							{
								std::cout << "Nothing\n";
								break;
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


	//UI Updating
	std::string toSet;
	toSet.append("Health   : ");
	toSet.append(std::to_string(Global::Player->health));
	toSet.append("\nStamina : ");
	toSet.append(std::to_string(Global::Player->stamina));
	PlayerStats->changeText(toSet.c_str());

	toSet.clear();
	toSet.append("Health   : ");
	toSet.append(std::to_string(e.health));
	toSet.append("\nStamina : ");
	toSet.append(std::to_string(e.stamina));
	EnemyStats->changeText(toSet.c_str());
}

void combat::changeButtons(char butt)
{


	int moveCount;
	int start;
	switch (butt)
	{
	case 'F':
		if (curDisplayed == 'F')
		{
			return;
		}

		for (size_t i = 0; i < 10; i++)
		{
			if (menu[i] != nullptr)
			{
				removeFromUI(menu[i]);
			}
		}

		curDisplayed = 'F';
		moveCount = Global::Player->moves.size();
		start = 0;
		if (moveCount > 8) { moveCount = 8; }
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



		for (size_t i = start; i < moveCount; i++)
		{
			textProps* p = new textProps();
			p->col = sf::Color::White;
			p->fontSize = 20;

			p->string = MoveController::getMove((uint32_t)moves[i]->getData())->name;
			moves.push_back(new Text(*p));
			moves[i + moveCount]->setPos(moves[i]->getPos().x, moves[i]->getPos().y - 5);

			UI.push_back(moves[i + moveCount]);

			delete p;
		}

		

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
		playerBlocks();
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
	bool pHit = false;
	uint32_t pDamage = 0;

	bool eHit = false;
	uint32_t eDamage = 0;

	srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());

	uint32_t rando = rand() % 101;

	if (rando < Global::Player->stats[1] + playerMove->accuracy)
	{
		pHit = true;
		int range = rand() % 41;
		range -= 20;
		if (range == 0)
		{
			range = 1;
		}
		range = (100 - (100 / range)) / 100;
		pDamage = ((playerMove->power / 100) * Global::Player->stats[0]) * playerMove->baseDamage;
		pDamage = pDamage * range;
		if (pDamage == 0)
		{
			pDamage = 1;
		}
	}
	else
	{
		pHit = false;
	}


	move* eMove;

	if (e.moves.size() == 1)
	{
		eMove = e.moves[0];
	}
	else if (false)
	{

	}
	else
	{
		eMove = e.moves[0];
	}

	rando = rand() % 101;

	if (rando < e.stats[1] + eMove->accuracy)
	{
		eHit = true;
		float range = rand() % 41;
		range -= 20;
		range = (100 - (100 / range)) / 100;
		eDamage = ((eMove->power / 100) * e.stats[0]) * eMove->baseDamage;
		eDamage = eDamage * range;
		if (eDamage == 0)
		{
			eDamage = 1;
		}
	}
	else
	{
		eHit = false;
	}

	std::string toadd;


	if ((rand() % 101) + (Global::Player->stats[1] + Global::Player->stats[2]) * playerMove->speedModifier < (rand() % 101) + (e.stats[1] + e.stats[2]) * eMove->speedModifier)
	{
		if (eHit == true)
		{
			Global::Player->health -= eDamage;
			toadd = "You were hit for  ";
			toadd.append(std::to_string(eDamage));
			toadd.append(" damage.");
			addHsitory(toadd.c_str());

			if (Global::Player->health <= 0)
			{
				Global::Player->health = 0;
				loadScene(PlayerDies);
				closeScene();
				return;
			}
		}
		else
		{
			addHsitory("Your enemy missed you");
		}
		if (pHit == true)
		{
			e.health -= pDamage;
			toadd = "You hit the enemy for ";
			toadd.append(std::to_string(pDamage));
			toadd.append(" damage.");
			addHsitory(toadd.c_str());
			if (e.health <= 0)
			{
				e.health = 0;
				loadScene(PlayerWins);
			}
		}
		else
		{
			addHsitory("You missed your enemy");
		}
		
		
	}
	else
	{
		if (pHit == true)
		{
			e.health -= pDamage;
			toadd = "You hit the enemy for ";
			toadd.append(std::to_string(pDamage));
			toadd.append(" damage.");
			addHsitory(toadd.c_str());
			if (e.health <= 0)
			{
				e.health = 0;
				loadScene(PlayerWins);
			}
		}
		else
		{
			addHsitory("Your missed your enemy");
		}
		if (eHit == true)
		{
			Global::Player->health -= eDamage;
			toadd = "You were hit for ";
			toadd.append(std::to_string(eDamage));
			toadd.append(" damage.");
			addHsitory(toadd.c_str());
			if (Global::Player->health <= 0)
			{
				Global::Player->health = 0;
				loadScene(PlayerDies);
				closeScene();
				return;
			}
		}
		else
		{
			addHsitory("The enemy missed you");
		}
	}


}

void combat::playerBlocks()
{
	uint32_t rando = rand() % 101;
	move* eMove;
	uint32_t eDamage = 0;
	std::string toadd;

	if (e.moves.size() == 1)
	{
		eMove = e.moves[0];
	}
	else if (false)
	{

	}
	else
	{
		eMove = e.moves[0];
	}

	rando = rand() % 101;

	if (rando < e.stats[1] + eMove->accuracy)
	{
		float range = rand() % 41;
		range -= 20;
		range = (100 - (100 / range)) / 100;
		eDamage = ((eMove->power / 100) * e.stats[0]) * eMove->baseDamage;
		eDamage = eDamage * range;
		eDamage = eDamage / 2;
		if (eDamage == 0)
		{
			eDamage = 1;
		}
		toadd = "You hit the enemy for ";
		toadd.append(std::to_string(eDamage));
		toadd.append(" damage.");
		addHsitory(toadd.c_str());

		Global::Player->health -= eDamage;
		if (Global::Player->health <= 0 )
		{
			Global::Player->health = 0;
			loadScene(PlayerDies);
			closeScene();
			return;
		}
	}
	{
		addHsitory("Your enemy missed you");
	}


}

void combat::addHsitory(const char* texty)
{
	for (int i = 0; i < 10; i++)
	{
		if (history[i] == " ")
		{
			history[i] = texty;
			writeHistory();
			return;
		}
	}

	for (int i = 0; i < 9; i++)
	{
		history[i] = history[i + 1];
	}
	history[9] = texty;
	writeHistory();
}

void combat::writeHistory()
{
	std::string towrite;
	for (int i = 0; i < 10; i++)
	{
		towrite.append(history[i]);
		towrite.append("\n");
	}

	historyText->updateText(towrite.c_str());
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
	*doneFight = 1;
	for (size_t i = 0; i < 10; i++)
	{
		delete menu[i];
	}
}

void combat::loadScene(scene* next)
{
	Global::curScene = next;
	closeScene();
}
