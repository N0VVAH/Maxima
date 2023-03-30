#include "tutorial.h"
#include "iostream"
#include "combat.h"
#include "Transitions.h"

Tutorial::Tutorial() { }

Tutorial::Tutorial(scene* preScene)
{
	prevScene = preScene;
	c.CharSetup("..\\assets\\images\\chartest.png", 100, 100);
	textureAtlasProps a = textureAtlasProps();
	a.timeBetween = 0.3;
	a.texturesInAtlas = 3;
	c.setTextureAtlas(a);
	c.updateTexture();
	render.push_back(&c);
	c.setPos(400, 400);

	Teach.CharSetup("..\\assets\\images\\TeachTest.png", 100, 100);
	Teach.setTextureAtlas(a);
	Teach.updateTexture();
	Teach.setPos(800, 400);
	render.push_back(&Teach);

	teachCollision = Square(sf::Color::Black, 120, 120);
	teachCollision.setPos(800, 400);

	a.texturesInAtlas = 5;
	for (size_t i = 0; i < 10; i++)
	{
		enemies[i] = new Square("..\\assets\\images\\slimemonster.png", 60, 60);
		enemies[i]->setTextureAtlas(a);
		enemies[i]->updateTexture();
		enemies[i]->setPos(std::rand() % 800, std::rand() % 800);
		enemies[i]->type = 'E';
		render.push_back(enemies[i]);
	}
}

void Tutorial::update(sf::RenderWindow* window, float dtime)
{
	//sprite updates
	c.update(dtime);
	Teach.update(dtime);
	for (int i = 0; i < 10; i++)
	{
		enemies[i]->update(dtime);
	}

	sceneClean();
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

	//Collision Detection
	if (teachCollision.getGlobalBounds().intersects(c.getGlobalBounds()))
	{

		if (chatboxShowing == false)
		{
			chatboxShowing = true;
			Global::ChatBox->setPos(800, 300);
			render.push_back(Global::ChatBox);
		}

	}
	else
	{
		if (chatboxShowing == true)
		{
			for (size_t i = 0; i < render.size(); i++)
			{
				if (render[i] == Global::ChatBox)
				{
					render.erase(render.begin() + i);
					chatboxShowing = false;
				}
			}
		}
	}

	for (size_t i = 0; i < sizeof(enemies) / sizeof(Square*); i++)
	{
		if (c.getGlobalBounds().intersects(enemies[i]->getGlobalBounds()))
		{
			combatScene = new combat(this, fightDone);

			if (TransitionController::playing == nullptr)
			{
				TransitionController::playTransition(0);
				return;
			}

			TransitionController::playing->reset();
			TransitionController::playing == nullptr;
			enemies[i]->setPos(-400, -400);


			loadScene(combatScene);
			return;
		}
	}




	//Event handling
	sf::Event* events = new sf::Event;
	while (window->pollEvent(*events))
	{
		switch ((*events).type)
		{

		case sf::Event::KeyPressed:

			if ((*events).key.code == sf::Keyboard::W)
			{
				c.movePos(0, -500 * dtime);
			}
			if ((*events).key.code == sf::Keyboard::S)
			{
				c.movePos(0, 500 * dtime);
			}
			if ((*events).key.code == sf::Keyboard::A)
			{
				c.movePos(-500 * dtime, 0);
			}
			if ((*events).key.code == sf::Keyboard::D)
			{
				c.movePos(500 * dtime, 0);
			}

			switch ((*events).key.code)
			{
			case sf::Keyboard::Escape:
				exitScene();
				break;

			default:
				break;
			}
			break;

			render[0] = &c;


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
}

void Tutorial::draw(sf::RenderTarget& target, sf::RenderStates states)
{
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

char Tutorial::inputHandler()
{
	return 'h';
}

void Tutorial::exitScene()
{
	Global::curScene = prevScene;
}

void Tutorial::closeScene()
{
	exitScene();
	delete this;
}

void Tutorial::loadScene(scene* load)
{
	Global::curScene = load;

}