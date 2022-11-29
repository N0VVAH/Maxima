#pragma once
#include "SFML/Window.hpp"
#include "scene.h"
#include <vector>


class Global
{
public:
	static sf::Window* window;
	static scene* curScene;

	static std::vector<scene*> toDelete;
};