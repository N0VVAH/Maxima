#pragma once
#include "moves.h"
#include <vector>

class player
{
public:
	player();
	const char* name = "ANAKIN SKYWALKER";
	std::vector<move*> moves;
	int health = 10;
	int stamina = 10;
	int maxhealth = 10;
	int maxstamina = 10;
};