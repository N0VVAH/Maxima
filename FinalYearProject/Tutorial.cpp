#include "tutorial.h"


Tutorial::Tutorial() { }

Tutorial::Tutorial(scene* preScene)
{
	prevScene = preScene;
}

void Tutorial::update(sf::RenderWindow* window)
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