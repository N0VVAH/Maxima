#pragma once
#include "scene.h"

class MainMenu : public scene
{
public:
	MainMenu();
	void update(sf::RenderWindow* window, float dtime) override;
	char inputHandler() override;
	void loadScene(scene*) override;
	void exitScene() override;
	void closeScene() override;

protected:

private:
};