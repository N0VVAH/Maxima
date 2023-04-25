#pragma once
#include "SFML/Window.hpp"
#include "scene.h"
#include "player.h"
#include "square.h"



class Global
{
public:
	static sf::Window* window;
	static scene* curScene;

	static std::vector<scene*> toDelete;
	static int framerate;

	static Square* ChatBox;

	static player* Player;

	static sf::View* mainView;
	static bool updateView;


	//Gameplay variables
	static bool haveSon;
};