#pragma once
#include "moves.h"
#include <vector>
#include "item.h"


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
	uint32_t gold = 0;

	//strength, Dexterity, Constitution, intelligence, wisdom, charisma
	int stats[6] = { 1, 1, 1, 1, 1, 1 };

	int invsize;
	std::vector<unsigned int> inv;
};