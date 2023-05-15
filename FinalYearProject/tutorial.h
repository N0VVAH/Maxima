#pragma once
#include "scene.h"
#include "globals.h"
#include "Charactor.h"
#include "textappear.h"

class Tutorial : public scene
{
public:
	Tutorial();
	Tutorial(scene*);
	void update(sf::RenderWindow* window, float dtime) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) override;
	char inputHandler() override;
	void exitScene() override;
	void closeScene() override;
	void loadScene(scene*) override;


protected:
	Charactor c;
	Square* enemies[10] = {};
	Square* fence[5] = {};
	Charactor Teach;
	int* fightDone = 0;
	bool beenInFight = false;
	scene* combatScene;
	textAppear* tutorialText;
	Square* background;

	//Colliders
	Square teachCollision;
	Square exit;

	//edge collider for scene
	Square House;
	Square leftSide;
	Square botSide;
	Square rightSide;
	Square topRightSide;
	Square topLeftSide;

private:
	bool chatboxShowing = false;
	bool paused = false;
};