#pragma once
#include "scene.h"
#include "globals.h"

class FightWon : public scene
{
public:
	FightWon(scene* prev);
	virtual void update(sf::RenderWindow* window, float dtime) override;
	//virtual void draw(sf::RenderTarget& target, sf::RenderStates states);
	virtual char inputHandler()  override;
	virtual void exitScene()  override;
	virtual void closeScene()  override;
	virtual void loadScene(scene*)  override;



private:


};