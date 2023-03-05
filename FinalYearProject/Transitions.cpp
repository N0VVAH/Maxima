#include "Transitions.h"

std::vector<Transition*> TransitionController::transitions;
Transition* TransitionController::playing;

Transition* TransitionController::getTransition(uint32_t id)
{
	if (transitions[id]->id == id)
	{
		return transitions[id];
	}
}