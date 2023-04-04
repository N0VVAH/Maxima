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

	//strength, Dexterity, Constitution, intelligence, wisdom, charisma
	int stats[6] = { 1, 1, 1, 1, 1, 1 };
};