#pragma once
//#include <vector>
#include "square.h"


class Transition
{
public:
	Transition() {};
	virtual void update(float timeStep) {};
	inline bool isDone() { return done; }
	virtual void reset() {};
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) = 0;
	uint32_t id;

protected:
	bool done = false;
};

class battleTransitionOne : public Transition
{
public:
	battleTransitionOne()
	{
		id = 0;
		barOne = new Square(sf::Color::Black, 1600, 200);

		barTwo = new Square(sf::Color::Black, 1600, 200);

		barThree = new Square(sf::Color::Black, 1600, 200);

		barFour = new Square(sf::Color::Black, 1600, 200);

		reset();
	}
	virtual void update(float timeStep) override
	{
		barOne->movePos(700 * timeStep, 0);
		barTwo->movePos(-700 * timeStep, 0);
		barThree->movePos(700 * timeStep, 0);
		barFour->movePos(-700 * timeStep, 0);
		if (barOne->getPos().x >= 799)
		{
			done = true;
		}
	}

	virtual void reset() override
	{
		barOne->setPos(-800, 100);
		barTwo->setPos(2400, 300);
		barThree->setPos(-800, 500);
		barFour->setPos(2400, 700);
		done = false;
	}
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) override
	{
		barOne->draw(target, states);
		barTwo->draw(target, states);
		barThree->draw(target, states);
		barFour->draw(target, states);
	}

private:
	Square* barOne;
	Square* barTwo;
	Square* barThree;
	Square* barFour;

};


class TransitionController
{
public:
	static void start()
	{
		transitions.reserve(4);
		Transition* temp = new battleTransitionOne();
		addTransition(temp);
	}

	static inline void addTransition(Transition* t) { transitions.push_back(t); }

	static Transition* getTransition(uint32_t id);

	static inline void playTransition(uint32_t id) { playing = getTransition(id); }

	static Transition* playing;

private:

	static std::vector<Transition*> transitions;
};

