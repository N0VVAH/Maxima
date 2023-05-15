#include "mainworldwest.h"
#include "Transitions.h"
#include "sound.h"
#include "combat.h"
#include <chrono>

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
	rightTrigger.setPos(1590, 400);

	if (Global::haveSon == false && Global::doneFirstQuest == false)
	{
		kidSave = new Square("..\\assets\\images\\kidtosave.png", 48, 48);
		kidSave->setPos(100, 400);

		render.push_back(kidSave);

		kidCage = new Square("..\\assets\\images\\cage.png", 128, 128);
		kidCage->setPos(100, 400);
		kidCage->setCollider({ 100, 400 }, { 128, 128 });

		kidtrigger = Square(sf::Color::Black, 150, 150);
		kidtrigger.setPos(100, 400);

		render.push_back(kidCage);
	}


	textProps p;
	p.col = sf::Color::Black;
	p.fontSize = 26;
	p.string = "The Kid Shouts:\nYou need to kill all the goblins first!";
	cantRightNow = new Text(p);
	cantRightNow->setPos(1000, 700);
	
	c.CharSetup("..\\assets\\images\\chartest.png", 100, 100);
	c.setCollider(sf::Vector2f(1400.0f, 400.0f) + sf::Vector2f(60.0f, 64.0f), { 64.0f, 64.0f });
	textureAtlasProps a = textureAtlasProps();
	a.timeBetween = 0.3;
	a.texturesInAtlas = 3;
	c.setTextureAtlas(a);
	c.updateTexture();
	render.push_back(&c);
	c.setPos(1400, 400);

	
	std::srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());
	for (size_t i = 0; i < 4; i++)
	{
		enemies[i] = new Square("..\\assets\\images\\goblin.png", 60, 60);
		a.texturesInAtlas = 4;
		a.timeBetween = 0.25;
		enemies[i]->setTextureAtlas(a);
		enemies[i]->updateTexture();
		here:
		enemies[i]->setPos((std::rand() % 800) + 50, (std::rand() % 700) + 50);
		for (int k = 0; k < i; k++)
		{
			if (Global::haveSon == false)
			{
				if (enemies[k]->getPos().x > kidSave->getPos().x - 80 && enemies[k]->getPos().x < kidSave->getPos().x + 80)
				{
					if (enemies[k]->getPos().y > kidSave->getPos().y - 50 && enemies[k]->getPos().y < kidSave->getPos().y + 50)
					{
						goto here;
					}
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

		wallColliders[0] = Square(sf::Color::Black, 1600, 10);
		wallColliders[0].setPos(800, 0);
		wallColliders[0].setCollider({ 1600, 10 }, { 800, 0 });
		render.push_back(&wallColliders[0]);

		wallColliders[1] = Square(sf::Color::Black, 10, 800);
		wallColliders[1].setPos(0, 400);
		wallColliders[1].setCollider({ 10, 800 }, { 0, 400 });
		render.push_back(&wallColliders[1]);

		wallColliders[2] = Square(sf::Color::Black, 1600, 10);
		wallColliders[2].setPos(800, 800);
		wallColliders[2].setCollider({ 1600, 10 }, { 800, 800 });
		render.push_back(&wallColliders[2]);
	}
}

void MainWorldWest::update(sf::RenderWindow* window, float dtime)
{
	//sprite updates
	if (paused == false)
	{

		if (TransitionController::playing != nullptr && TransitionController::playing->isDone() == false)
		{
			TransitionController::playing->update(dtime);
			return;
		}
		Global::ChatBox->setPos(1000, 700);
		Global::ChatBox->setSize(500, 150);
		if (noEnemy == true && Global::haveSon == true && Global::doneFirstQuest == false)
		{
			sf::Vector2f dir1 = c.getPos();
			sf::Vector2f dir2 = kidSave->getPos();
			sf::Vector2f dir = (dir1 - dir2);
			kidSave->movePos(dir.x * dtime, dir.y * dtime);
		}

		noEnemy = true;
		for (size_t i = 0; i < 4; i++)
		{
			if (enemies[i]->getPos().x > 0)
			{
				noEnemy = false;
			}
		}
		if (noEnemy == true)
		{
			removeFromRender(kidCage);
		}

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
			if ((*events).key.code == sf::Keyboard::Escape)
			{
				paused = !paused;
				return;
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
	if (paused)
	{
		return;
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
	if (Global::haveSon == false)
	{
		if (c.Collider.getGlobalBounds().intersects(kidtrigger.getGlobalBounds()) )
		{
			if (noEnemy == true)
			{
				kidtrigger.setPos(-400, -400);
				cantRightNow->updateText("Ill follow you back to my mum!");
				removeFromRender(cantRightNow);
				removeFromRender(Global::ChatBox);
				render.push_back(Global::ChatBox);
				render.push_back(cantRightNow);
				Global::haveSon = true;
			}
			else
			{
				render.push_back(Global::ChatBox);
				render.push_back(cantRightNow);
			}
		}
	}
	for (int i = 0; i < 4; i++)
	{
		if (c.Collider.getGlobalBounds().intersects(enemies[i]->getGlobalBounds()))
		{

			if (TransitionController::playing == nullptr)
			{
				TransitionController::playTransition(0);
				return;
			}

			TransitionController::playing->reset();
			TransitionController::playing = nullptr;
			removeFromRender(enemies[i]);
			enemies[i]->setPos(-400, -400);

			Enemy e = Enemy();
			e.name = "Goblin Scout";
			e.health = 2;
			e.maxhealth = 2;
			e.loottable[0] = 3;
			e.texture = "..\\assets\\images\\goblin.png";
			e.texInAtlas = 4;
			e.moves.push_back(MoveController::getMove(10));

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
