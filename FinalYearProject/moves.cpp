#include "moves.h"
std::vector<move*> MoveController::moves = std::vector<move*>();


MoveController::MoveController()
{
	moves.reserve(16);
	moves.push_back(new move());
}

move* MoveController::getMove(uint32_t id)
{
	if (moves[id]->id == id)
	{
		return moves[id];
	}

	for (size_t i = 0; i < moves.size(); i++)
	{
		if (moves[i]->id == id)
		{
			return moves[i];
		}
	}
}