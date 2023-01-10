#include "mainmenu.h"
#include <chrono>
#include <thread>
#include "globals.h"
#include "iostream"

scene* Global::curScene = nullptr;
int Global::framerate = 144;

int main()
{
	
	sf::RenderWindow window(sf::VideoMode(1600, 800), "Maxima");

	Global::window = &window;

	window.setVerticalSyncEnabled(true);

	Global::curScene = new MainMenu();


	sf::Clock clock;
	sf::Time start;
	sf::Time end;
	sf::Time dTime;

	clock.restart();

	clock.restart();
	while (window.isOpen())
	{
		start = clock.getElapsedTime();

		window.clear();		
		if ((end - start).asSeconds() > 1.0 / Global::framerate)
		{
			Global::curScene->update(&window, 1.0 / Global::framerate);
		}
		else
		{
			Global::curScene->update(&window, (end - start).asSeconds());
		}
		Global::curScene->draw(window, sf::RenderStates::Default);
		window.display();

		end = clock.getElapsedTime();
		clock.restart();
	}

	return 0;
}