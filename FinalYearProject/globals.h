#pragma once
#include "SFML/Window.hpp"
#include "scene.h"
#include <vector>
#include "square.h"


class Global
{
public:
	static sf::Window* window;
	static scene* curScene;

	static std::vector<scene*> toDelete;
	static int framerate;

	static Square* ChatBox;
};