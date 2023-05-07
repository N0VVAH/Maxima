#include "buttonfuncs.h"
#include "tutorial.h"
#include "mainmenu.h"
#include <iostream>

sf::Window* Global::window = nullptr;

//Main Menu
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

//Fight Menu
char Fight()
{
	return 'F';
}

char Block()
{
	return 'b';
}

char Inv()
{
	return 'i';
}

char Flee()
{
	return 'f';
}

//DeathScene
void loadMainMenu()
{
	Global::curScene = new MainMenu();
}