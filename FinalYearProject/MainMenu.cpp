#include "mainmenu.h"
#include <iostream>


MainMenu::MainMenu()
{
	circle = sf::CircleShape(100.f);
	circle.setFillColor(sf::Color::Blue);
	circle.setPosition(200, 200);
}


void MainMenu::update(sf::RenderWindow* window)
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
				mouseDownPos = sf::Mouse::getPosition();
			}
			
			break;

		case sf::Event::MouseButtonReleased:
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == false && mouseDownPos != sf::Vector2i())
			{
				mouseDownPos = sf::Vector2i();
			}
	
		default:
			break;
		}
	}

}

char MainMenu::inputHandler()
{
	return '0';
}

void MainMenu::draw(sf::RenderTarget& target, sf::RenderStates states)
{

	target.draw(circle, states);
	
}

