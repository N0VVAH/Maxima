#pragma once
#include "moves.h"
#include <vector>
#include "item.h"


class player
{
public:
	player()
	{
		name = "Adventurer";
		health = 10;
		stamina = 10;
		maxhealth = 10;
		maxstamina = 10;
		gold = 0;
		for (size_t i = 0; i < 6; i++)
		{
			stats[i] = 1;
		}
		moves.empty();
		inv.empty();
		invsize = 6;
	};
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