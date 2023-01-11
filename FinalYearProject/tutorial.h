#pragma once
#include "scene.h"
#include "globals.h"
#include "Charactor.h"
#include "square.h"

class Tutorial : public scene
{
public:
	Tutorial();
	Tutorial(scene*);
	void update(sf::RenderWindow* window, float dtime) override;
	//void draw(sf::RenderTarget& target, sf::RenderStates states);
	char inputHandler() override;
	void exitScene() override;
	void closeScene() override;
	void loadScene(scene*) override;

protected:
	Charactor c;
	Square* enemies[10] = {};
};