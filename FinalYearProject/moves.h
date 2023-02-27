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
	uint32_t id;
	const char* name;
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