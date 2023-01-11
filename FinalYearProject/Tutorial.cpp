#include "tutorial.h"
#include "iostream"

Tutorial::Tutorial() { }

Tutorial::Tutorial(scene* preScene)
{
	prevScene = preScene;
	c.CharSetup(sf::Color::Green);
	render.push_back(&c);
	c.setPos(400, 400);
	for (size_t i = 0; i < 10; i++)
	{
		enemies[i] = Square(sf::Color::Red);
		enemies[i].setPos(std::rand() % 800, std::rand() % 800);
		render.push_back(&enemies[i]);
	}
}

void Tutorial::update(sf::RenderWindow* window, float dtime)
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
				exitScene();
				break;

			case sf::Keyboard::W:
				c.movePos(0, -500 * dtime);
				break;
			case sf::Keyboard::S:
				c.movePos(0, 500 * dtime);
				break;
			case sf::Keyboard::A:
				c.movePos(-500 * dtime, 0);
				break;
			case sf::Keyboard::D:
				c.movePos(500 * dtime, 0);
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