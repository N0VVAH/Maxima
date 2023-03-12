#pragma once
#include <vector>


class move
{
public:
	/// Default Constructor used only for testing
	move()
	{
		id = 0;
		name = "test";
	}
	move(uint32_t i, const char* n, uint32_t ai, uint32_t p, uint32_t a, const char* t, float sm, uint32_t bd)
	{
		id = i;
		name = n;
		animationID = ai;
		power = p;
		accuracy = a;
		type = t;
		speedModifier = sm;
		baseDamage = bd;
	}

	uint32_t id;
	const char* name;
	uint32_t animationID;

	uint32_t power;
	uint32_t accuracy;
	float speedModifier;
	uint32_t baseDamage;


	const char* type;
};

class MoveController
{
public:
	//Functions
	///non static
	MoveController();

	///Static
	static move* getMove(uint32_t id);

	//Variables
	///static
	static std::vector<move*> moves;

};