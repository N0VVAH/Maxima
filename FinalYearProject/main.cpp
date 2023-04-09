#include "mainmenu.h"
#include <chrono>
#include <thread>
#include "globals.h"
#include "iostream"
#include "Transitions.h"

void startUp();

scene* Global::curScene = nullptr;
int Global::framerate = 60;
Square* Global::ChatBox = new Square("..\\assets\\images\\textbox.png", 450, 150);
player* Global::Player = new player();
sf::View* Global::mainView = new sf::View();
bool Global::updateView = false;

int main()
{

	sf::RenderWindow window(sf::VideoMode(1600, 800), "Maxima");

	startUp();

	sf::View* mainView;
	mainView = new sf::View(sf::FloatRect(0.0, 0.0, 1600.0f, 800.0f));
	window.setView(*mainView);

	Global::mainView = mainView;

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
		if (Global::updateView == true)
		{
			window.setView(*Global::mainView);
			Global::updateView = false;
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

	ItemManager::ItemManager();
}