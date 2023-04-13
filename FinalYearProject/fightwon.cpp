#include "fightwon.h"
#include <chrono>

FightWon::FightWon(scene* prev, Enemy en)
{
	e = en;
	std::srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());
	prevScene = prev;

	done = Square(sf::Color::White, 150, 50);
	done.setPos(1400, 700);
	done.type = 'b';
	UI.push_back(&done);



	uint32_t gold = std::rand() % 10;// *e.difficulty;
	textProps p;
	p.col = sf::Color::White;
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


	p.col = sf::Color::Black;
	p.string = "Done";
	tDone = new Text(p);
	tDone->setPos(1400, 700);

	UI.push_back(tDone);


	for (int i = 0; i < 20; i++)
	{
		if (e.loottable[i] != -1)
		{
			items[i] = new Square(*ItemManager::getTexture(e.loottable[i]), 96, 96);
			//delete it;
			items[i]->setPos(400 + (150 * (i % 5)), 200 + (150 * (i / 5)));
			UI.push_back(items[i]);
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
	delete Gold;
	delete YourInv;
	delete LootAbleItems;
}

void FightWon::loadScene(scene*)
{

}
