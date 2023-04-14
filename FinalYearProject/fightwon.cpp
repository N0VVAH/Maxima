#include "fightwon.h"
#include <chrono>
#include <iostream>

FightWon::FightWon(scene* prev, Enemy en)
{
	e = en;
	std::srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());
	prevScene = prev;

	background = new Square("..\\assets\\images\\backgrounds\\playerwin.png", 1600, 800);
	background->setPos(800, 400);
	render.push_back(background);

	done = Square(sf::Color::Black, 150, 50);
	done.setPos(1400, 710);
	done.type = 'b';
	UI.push_back(&done);

	try
	{
		grey.loadFromFile("..\\assets\\images\\icons\\greyedout.png");
	}
	catch (const std::exception& e)
	{
		std::cout << "ERROR LOADING GEEDOUT TEXTURE IS AS FOLLOWS" << e.what() << "\n";
	}




	uint32_t gold = std::rand() % 10;// *e.difficulty;
	textProps p;
	p.col = sf::Color::Black;
	p.fontSize = 30.f;
	std::string temp = "Gold Picked Up: ";
	temp.append(std::to_string(gold));
	p.string = temp.c_str();
	Gold = new Text(p);
	Gold->setPos(150, 50);

	UI.push_back(Gold);

	p.string = "Available Items to Loot";
	LootAbleItems = new Text(p);
	LootAbleItems->setPos(1000, 50);
	
	UI.push_back(LootAbleItems);


	p.col = sf::Color::White;
	p.string = "Done";
	tDone = new Text(p);
	tDone->setPos(1400, 700);

	UI.push_back(tDone);

	CollectedItems = std::vector<int>();

	for (int i = 0; i < 20; i++)
	{
		if (e.loottable[i] != -1)
		{
			items[i] = new Square(*ItemManager::getTexture(e.loottable[i]), 96, 96);
			items[i]->setPos(400 + (150 * (i % 5)), 200 + (150 * (i / 5)));
			items[i]->setData((void*) e.loottable[i]);
			items[i]->type = 'i';
			UI.push_back(items[i]);

			greyedout[i] = Square(grey, 96, 96);
			greyedout[i].setPos(400 + (150 * (i % 5)), 200 + (150 * (i / 5)));
			greyedout->setTransparency(128);
		}
	}
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
				mouseDownPos = { events->mouseButton.x, events->mouseButton.y };
			}

			break;

		case sf::Event::MouseButtonReleased:
			mouseUpPos = { events->mouseButton.x, events->mouseButton.y };
			for (size_t i = 0; i < UI.size(); i++)
			{
				if (UI[i]->getGlobalBounds().contains(mouseDownPos.x, mouseDownPos.y) && UI[i]->getGlobalBounds().contains(mouseUpPos.x, mouseUpPos.y))
				{
					if (UI[i]->type == 'b')
					{
						exitScene();
						return;
					}
					if (UI[i]->type == 'i')
					{
						UI[i]->type = 'p';
						for (int k = 0; k < 20; k++)
						{
							if (items[k] == UI[i])
							{
								int itemID = (int)UI[i]->getData();
								CollectedItems.push_back(itemID);
								UI.push_back(&greyedout[k]);
							}
						}

					}
					else if (UI[i]->type == 'p')
					{
						UI[i]->type = 'i';
						int itemID = (int)UI[i]->getData();
						for (int p = 0; p < CollectedItems.size(); p++)
						{
							if (CollectedItems[p] == itemID)
							{
								CollectedItems.erase(CollectedItems.begin() + p);
								for (int k = 0; k < 20; k++)
								{
									if (items[k] == UI[i])
									{
										removeFromUI(&greyedout[k]);
									}
								}
								break;
							}
						}
					}
				}
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
	closeScene();
	Global::curScene = prevScene;
}

void FightWon::closeScene()
{
	for (size_t i = 0; i < CollectedItems.size(); i++)
	{
		Global::Player->inv.push_back(CollectedItems[i]);
	}
	delete Gold;
	delete YourInv;
	delete LootAbleItems;
	for (size_t i = 0; i < 20; i++)
	{
		if (items[i] != nullptr)
		{
			delete items[i];
		}
	}
	delete tDone;
	delete background;
}

void FightWon::loadScene(scene*)
{

}
