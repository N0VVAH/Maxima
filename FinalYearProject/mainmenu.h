#pragma once
#include "scene.h"

class MainMenu : public scene
{
public:
	MainMenu();
	void update(sf::RenderWindow* window) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) override;
	char inputHandler() override;
	void loadScene(scene*) override;
	void exitScene() override;
	void closeScene() override;

protected:

private:
};