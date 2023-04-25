#pragma once
#include "scene.h"
#include "globals.h"
#include "Charactor.h"
#include "textappear.h"

class MainWorldWest : public scene
{
public:
	MainWorldWest();
	MainWorldWest(scene*);
	void update(sf::RenderWindow* window, float dtime) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) override;
	char inputHandler() override;
	void exitScene() override;
	void closeScene() override;
	void loadScene(scene*) override;


protected:
	Charactor c;
	Square* enemies[4] = {};

	Square* kidSave;
	Square* kidCage;

	Text* questGiverText;
	textAppear* questGiverGive;
	int textQuestGiverver = 0;


	sf::Texture hedgeTex;
	sf::Texture houseTex;

	Square rightTrigger;

	scene* combatScene;
	int* fightDone = new int(0);

	Square* background;

	bool renderCollider = false;

private:
};