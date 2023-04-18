#include "mainworld.h"
#include "Transitions.h"
#include "sound.h"

MainWorld::MainWorld()
{
}

MainWorld::MainWorld(scene* s)
{
	prevScene = s;

	background = new Square("..\\assets\\images\\backgrounds\\mainworld.png", 1600, 800);
	background->setPos(800, 400);

	//SoundsController::playSound(0, true);
	hedgeTex.loadFromFile("..\\assets\\images\\hedge.png");
	houseTex.loadFromFile("..\\assets\\images\\genhouse.png");

	hedges[0] = new Square(hedgeTex, 128, 64);
	hedges[0]->setPos(950, 32);
	hedges[0]->setCollider(sf::Vector2f(950, 32), sf::Vector2f(128, 48));
	render.push_back(hedges[0]);

	hedges[1] = new Square(hedgeTex, 128, 64);
	hedges[1]->setPos(1078, 32);
	hedges[1]->setCollider(sf::Vector2f(1058, 32), sf::Vector2f(128, 48));
	render.push_back(hedges[1]);

	hedges[2] = new Square(hedgeTex, 128, 64);
	hedges[2]->setPos(1156, 32);
	hedges[2]->setCollider(sf::Vector2f(1156, 32), sf::Vector2f(128, 48));
	render.push_back(hedges[2]);

	hedges[4] = new Square(hedgeTex, 128, 64);
	hedges[4]->setPos(1220, 32);
	hedges[4]->setCollider(sf::Vector2f(1200, 32), sf::Vector2f(128, 48));
	render.push_back(hedges[4]);

	hedges[3] = new Square(hedgeTex, 128, 64);
	hedges[3]->setPos(1568, 425);
	hedges[3]->setCollider(sf::Vector2f(1568, 425), sf::Vector2f(128, 48));
	hedges[3]->setRotation(90.0f);
	render.push_back(hedges[3]);


	houses[0] = new Square(houseTex, 320, 320);
	houses[0]->setPos(900, 700);
	houses[0]->setCollider(sf::Vector2f(900, 700), sf::Vector2f(320, 320));
	render.push_back(houses[0]);

	houses[1] = new Square(houseTex, 320, 320);
	houses[1]->setPos(1220, 740);
	houses[1]->setCollider(sf::Vector2f(1220, 740), sf::Vector2f(320, 320));
	render.push_back(houses[1]);

	houses[2] = new Square(houseTex, 320, 320);
	houses[2]->setPos(1540, 650);
	houses[2]->setCollider(sf::Vector2f(1540, 650), sf::Vector2f(320, 320));
	render.push_back(houses[2]);

	houses[3] = new Square(houseTex, 320, 320);
	houses[3]->setPos(160, 120);
	houses[3]->setCollider(sf::Vector2f(160, 120), sf::Vector2f(320, 320));
	render.push_back(houses[3]);

	houses[4] = new Square(houseTex, 320, 320);
	houses[4]->setPos(480, 20);
	houses[4]->setCollider(sf::Vector2f(480, 20), sf::Vector2f(320, 320));
	render.push_back(houses[4]);

	shop = new Square("..\\assets\\images\\shop.png", 320, 320);
	shop->setPos(800, 50);
	shop->setCollider(sf::Vector2f(800, 50), sf::Vector2f(320, 320));
	render.push_back(shop);

	questGiver = new Square("..\\assets\\images\\womenquestgiver.png", 80, 80);
	questGiver->setPos(800, 490);
	questGiver->setCollider(sf::Vector2f(800, 490), sf::Vector2f(64, 64));
	render.push_back(questGiver);

	henArea = new Square("..\\assets\\images\\hen.png", 640, 640);
	henArea->setPos(1600, 100);
	henArea->setCollider({ 1500, 150 }, { 320, 320 });
	render.push_back(henArea);

	c.CharSetup("..\\assets\\images\\chartest.png", 100, 100);
	c.setCollider(sf::Vector2f(600.0f, 700.0f) + sf::Vector2f(60.0f, 64.0f), { 64.0f, 64.0f });
	textureAtlasProps a = textureAtlasProps();
	a.timeBetween = 0.3;
	a.texturesInAtlas = 3;
	c.setTextureAtlas(a);
	c.updateTexture();
	render.push_back(&c);
	c.setPos(600, 700);


	for (size_t i = 0; i < 10; i++)
	{
		enemies[i] = new Square("..\\assets\\images\\slimemonster.png", 60, 60);
		enemies[i]->setTextureAtlas(a);
		enemies[i]->updateTexture();
		enemies[i]->setPos((std::rand() % 700) + 850, (std::rand() % 600) + 50);
		enemies[i]->type = 'E';
	}
}

void MainWorld::update(sf::RenderWindow* window, float dtime)
{
	//sprite updates
	c.update(dtime);
	for (int i = 0; i < 10; i++)
	{
		enemies[i]->update(dtime);
	}


	if (fightDone == new bool(true))
	{
		delete fightDone;
		delete combatScene;
	}



	if (TransitionController::playing != nullptr && TransitionController::playing->isDone() == false)
	{
		TransitionController::playing->update(dtime);
		return;
	}


	//Event handling
	sf::Event* events = new sf::Event;
	while (window->pollEvent(*events))
	{
		switch ((*events).type)
		{

		case sf::Event::KeyPressed:
			if ((*events).key.code == sf::Keyboard::Enter)
			{

			}



			switch ((*events).key.code)
			{
			case sf::Keyboard::Escape:
				break;

			default:
				break;
			}
			break;

			render[0] = &c;

		case sf::Event::KeyReleased:
			if ((*events).key.code == sf::Keyboard::Enter)
			{
				renderCollider = !renderCollider;
			}
			break;

		case sf::Event::Closed:
			(*window).close();
			break;

		case sf::Event::MouseButtonPressed:
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				mouseDownPos = sf::Mouse::getPosition();
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


	sf::Vector2f movement = sf::Vector2f(0.0f, 0.0f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		movement += sf::Vector2f(0, -100 * dtime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		movement += sf::Vector2f(0, 100 * dtime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		movement += sf::Vector2f(-100 * dtime, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		movement += sf::Vector2f(100 * dtime, 0);
	}

	c.movePos(movement.x, movement.y);

	//Collision Detection
	for (int i = 0; i < render.size(); i++)
	{
		if (render[i]->hasCollider == true)
		{
			if (render[i] == &c)
			{
				continue;
			}
			if (c.Collider.getGlobalBounds().intersects(render[i]->Collider.getGlobalBounds()))
			{
				c.movePos(-movement.x, -movement.y);
				break;
			}
		}
	}
}

void MainWorld::draw(sf::RenderTarget& target, sf::RenderStates states)
{
	background->draw(target, states);

	for (size_t i = 0; i < render.size(); i++)
	{
		render[i]->draw(target, states);
	}

	for (size_t i = 0; i < UI.size(); i++)
	{
		UI[i]->draw(target, states);
	}

	if (TransitionController::playing != nullptr && TransitionController::playing->isDone() == false)
	{
		TransitionController::playing->draw(target, states);
		return;
	}

	if (renderCollider == true)
	{
		for (size_t i = 0; i < render.size(); i++)
		{
			if (render[i]->hasCollider == true)
			{
				target.draw(render[i]->Collider, states);
			}
		}
	}
}

char MainWorld::inputHandler()
{
	return 0;
}

void MainWorld::exitScene()
{
}

void MainWorld::closeScene()
{
}

void MainWorld::loadScene(scene*)
{
}
