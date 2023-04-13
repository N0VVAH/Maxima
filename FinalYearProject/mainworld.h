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
	Square* enemies[10] = {};

	scene* combatScene;
	bool* fightDone = new bool(false);

	Square* background;


private:
};