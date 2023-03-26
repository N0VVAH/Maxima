#pragma once
#include "scene.h"


class PlayerDeath : public scene
{
public:
	PlayerDeath(scene* ls);
	virtual void update(sf::RenderWindow* window, float dtime) override;
	//virtual void draw(sf::RenderTarget& target, sf::RenderStates states);
	virtual char inputHandler()  override;
	virtual void exitScene()  override;
	virtual void closeScene()  override;
	virtual void loadScene(scene*)  override;


private:

	sprite* quit;
	sprite* quitText;
	sprite* loadLastSave;
	sprite* loadText;
	Square backGround = Square(sf::Color::White, 1600, 800);


};