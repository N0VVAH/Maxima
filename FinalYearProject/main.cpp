#include "mainmenu.h"
#include <chrono>
#include <thread>
#include "globals.h"
#include "iostream"
#include "Transitions.h"

void startUp();

scene* Global::curScene = nullptr;
int Global::framerate = 60;
Square* Global::ChatBox = new Square("D:\\Files\\UNI year 3 Work\\Final Year Project\\Maxima\\x64\\Debug\\ChatBox.png", 450, 150);
player* Global::Player = new player();

int main()
{
	startUp();


	sf::RenderWindow window(sf::VideoMode(1600, 800), "Maxima");

	Global::window = &window;

	window.setVerticalSyncEnabled(true);

	Global::curScene = new MainMenu();


	sf::Clock clock;
	sf::Time start;
	sf::Time end;

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


void startUp()
{
	TransitionController::start();

	MoveController::MoveController();
}