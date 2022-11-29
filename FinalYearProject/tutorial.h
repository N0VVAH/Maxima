#pragma once
#include "scene.h"
#include "globals.h"

class Tutorial : public scene
{
public:
	Tutorial();
	Tutorial(scene*);
	void update(sf::RenderWindow* window) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) override;
	char inputHandler() override;
	void exitScene() override;
	void closeScene() override;
	void loadScene(scene*) override;

protected:

};