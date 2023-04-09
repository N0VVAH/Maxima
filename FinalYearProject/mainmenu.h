#pragma once
#include "scene.h"
#include "text.h"

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
	Square* background;
	Square* player;
	sf::Vector2f viewPos;
	float yMovement = 0.0f;
	float xMovement = 0.0f;

};