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
	Square fence[14] = {};
	Charactor Teach;
	Square teachCollision;
	bool* fightDone = new bool(false);
	scene* combatScene;
	textAppear* tutorialText;

private:
	bool chatboxShowing = false;
};