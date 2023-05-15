#pragma once
#include "scene.h"
#include "globals.h"
#include "Charactor.h"
#include "textappear.h"

class MainWorld : public scene
{
public:
	MainWorld();
	MainWorld(scene*);
	void update(sf::RenderWindow* window, float dtime) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) override;
	char inputHandler() override;
	void exitScene() override;
	void closeScene() override;
	void loadScene(scene*) override;


protected:
	Charactor c;
	Square* questGiver;
	Square questGiverContact;
	Square* enemies[10] = {};
	Square* kidSave;

	Text* questGiverText;
	textAppear* questGiverGive;
	int textQuestGiverver = 0;
	

	sf::Texture hedgeTex;
	sf::Texture houseTex;


	Square* hedges[5];
	Square* houses[5];
	Square* shop;
	Square* henArea;

	Square bottomStop;
	Square leftTrigger;

	scene* combatScene;
	bool* fightDone = new bool(false);

	Square* background;

	bool renderCollider = false;

private:
	bool paused = false;
};