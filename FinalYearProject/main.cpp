#include "mainmenu.h"
#include <chrono>
#include <thread>



int main()
{
	
	sf::RenderWindow window(sf::VideoMode(1600, 800), "Maxima");

	scene* current = new MainMenu();

	auto end = std::chrono::high_resolution_clock::now();

	auto start = end;

	while (window.isOpen())
	{
		start = std::chrono::high_resolution_clock::now();

		window.clear();
		current->update(&window);
		current->draw(window, sf::RenderStates::Default);
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