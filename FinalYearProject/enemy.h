#pragma once

class Enemy
{
public:
	const char* name = "?";

	std::vector<move*> moves;

	int health = 10;
	int stamina = 10;
	int maxhealth = 10;
	int maxstamina = 10;

	const char* texture;

	//strength, Dexterity, Constitution, intelligence, wisdom, charisma
	int stats[6] = { 1, 1, 1, 1, 1, 1 };

	uint32_t difficulty = 1;
	int loottable[20] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, };
};