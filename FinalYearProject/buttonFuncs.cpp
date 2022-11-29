#include "buttonfuncs.h"
#include <iostream>

sf::Window* Global::window = nullptr;

scene* clickStart()
{
	scene* w = new Tutorial(Global::curScene);
	return w;
}

void clickSettings()
{
	//this needs to load settings menu
}

void clickQuick()
{
	Global::window->close();
}