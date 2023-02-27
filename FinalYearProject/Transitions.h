#pragma once
#include <vector>


class Transition
{
public:
	Transition();
	void update();
};

class TransitionController
{
public:
	TransitionController();

	static inline void addTransition(Transition* t) { transitions.push_back(t); }

	static void playTransition();


private:

	static std::vector<Transition*> transitions;
};