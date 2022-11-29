#include "mainmenu.h"
#include <chrono>
#include <thread>
#include "globals.h"

scene* Global::curScene = nullptr;

int main()
{
	
	sf::RenderWindow window(sf::VideoMode(1600, 800), "Maxima");

	Global::window = &window;

	Global::curScene = new MainMenu();

	auto end = std::chrono::high_resolution_clock::now();

	auto start = end;

	while (window.isOpen())
	{
		start = std::chrono::high_resolution_clock::now();

		window.clear();
		Global::curScene->update(&window);
		Global::curScene->draw(window, sf::RenderStates::Default);
		window.display();


		end = std::chrono::high_resolution_clock::now();
		if (end - start < std::chrono::milliseconds(16))
		{
			auto sleepfor = std::chrono::milliseconds(16) - (end - start);
			std::this_thread::sleep_for(sleepfor);
		}

	}

	return 0;
}