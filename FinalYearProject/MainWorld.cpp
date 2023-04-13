#include "mainworld.h"
#include "Transitions.h"

MainWorld::MainWorld()
{
}

MainWorld::MainWorld(scene* s)
{
	prevScene = s;

	background = new Square(sf::Color::Black, 1600, 800);
	background->setPos(800, 400);

	c.CharSetup("..\\assets\\images\\chartest.png", 100, 100);
	c.setCollider({ 250.0f, 450.0f }, { 64.0f, 64.0f });
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
