#include "mainworldwest.h"
#include "Transitions.h"
#include "sound.h"
#include "combat.h"

MainWorldWest::MainWorldWest()
{
}

MainWorldWest::MainWorldWest(scene* s)
{
	prevScene = s;

	background = new Square("..\\assets\\images\\backgrounds\\mainworldwest.png", 1600, 800);
	background->setPos(800, 400);

	//SoundsController::playSound(0, true);
	hedgeTex.loadFromFile("..\\assets\\images\\hedge.png");
	houseTex.loadFromFile("..\\assets\\images\\genhouse.png");


	rightTrigger = Square(sf::Color::Black, 10, 800);
	rightTrigger.setPos(1590, 800);

	kidSave = new Square("..\\assets\\images\\kidtosave.png", 48, 48);
	kidSave->setPos(100, 400);

	render.push_back(kidSave);

	kidCage = new Square("..\\assets\\images\\cage.png", 128, 128);
	kidCage->setPos(100, 400);

	render.push_back(kidCage);
	
	c.CharSetup("..\\assets\\images\\chartest.png", 100, 100);
	c.setCollider(sf::Vector2f(1400.0f, 400.0f) + sf::Vector2f(60.0f, 64.0f), { 64.0f, 64.0f });
	textureAtlasProps a = textureAtlasProps();
	a.timeBetween = 0.3;
	a.texturesInAtlas = 3;
	c.setTextureAtlas(a);
	c.updateTexture();
	render.push_back(&c);
	c.setPos(1400, 400);

	

	for (size_t i = 0; i < 4; i++)
	{
		enemies[i] = new Square("..\\assets\\images\\goblin.png", 60, 60);
		a.texturesInAtlas = 4;
		a.timeBetween = 0.25;
		enemies[i]->setTextureAtlas(a);
		enemies[i]->updateTexture();
		here:
		enemies[i]->setPos((std::rand() % 600) + 50, (std::rand() % 600) + 50);
		for (int k = 0; k < i; k++)
		{
			if (enemies[k]->getPos().x > kidSave->getPos().x - 100 && enemies[k]->getPos().x < kidSave->getPos().x + 100)
			{
				if (enemies[k]->getPos().y > kidSave->getPos().y - 100 && enemies[k]->getPos().y < kidSave->getPos().y + 100)
				{
					goto here;
				}
			}
			if (k != i)
			{
				if (enemies[k]->getPos().x > enemies[i]->getPos().x - 30 && enemies[k]->getPos().x < enemies[i]->getPos().x + 60)
				{
					if (enemies[k]->getPos().y > enemies[i]->getPos().y - 30 && enemies[k]->getPos().y < enemies[i]->getPos().y + 60)
					{
						goto here;
					}
				}
			}
		}
		enemies[i]->type = 'E';
		render.push_back(enemies[i]);
	}
}

void MainWorldWest::update(sf::RenderWindow* window, float dtime)
{
	//sprite updates
	c.update(dtime);
	for (int i = 0; i < 4; i++)
	{
		enemies[i]->update(dtime);
	}


	if (fightDone == new int(1))
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
				questGiverGive->changeSpeed(0.025f);
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
				if (questGiverGive->getSpeed() != 0.05f)
				{
					questGiverGive->changeSpeed(0.05f);
				}
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

	if (c.Collider.getGlobalBounds().intersects(rightTrigger.getGlobalBounds()))
	{
		loadScene(prevScene);
	}

	for (int i = 0; i < 4; i++)
	{
		if (c.Collider.getGlobalBounds().intersects(enemies[i]->getGlobalBounds()))
		{
			Enemy e = Enemy();
			e.name = "Goblin Scout";
			e.health = 15;
			e.maxhealth = 15;
			e.loottable[0] = 3;
			e.texture = "..\\assets\\images\\goblin.png";
			e.texInAtlas = 4;

			loadScene(new combat(this, fightDone, e));
		}
	}

	for (int i = 0; i < render.size(); i++)
	{
		if (render[i]->hasCollider == true)
		{
			if (render[i] == &c)
			{
				continue;
			}
			if (c.Collider.getGlobalBounds().intersects(render[i]->getGlobalBounds()))
			{
				c.movePos(-movement.x, -movement.y);
				break;
			}
		}
	}
}

void MainWorldWest::draw(sf::RenderTarget& target, sf::RenderStates states)
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

char MainWorldWest::inputHandler()
{
	return 0;
}

void MainWorldWest::exitScene()
{
}

void MainWorldWest::closeScene()
{
}

void MainWorldWest::loadScene(scene* newS)
{
	Global::curScene = newS;
}
