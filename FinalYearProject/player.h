#pragma once
#include "moves.h"
#include <vector>

class player
{
public:
	player();
	const char* name;
	std::vector<move*> moves;
};