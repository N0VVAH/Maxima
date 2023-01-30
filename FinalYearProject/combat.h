#pragma once
#include "scene.h"
#include "globals.h"

class combat : public scene
{
public:
	combat(scene* prev);
	virtual void update(sf::RenderWindow* window, float dtime) override;
	//virtual void draw(sf::RenderTarget& target, sf::RenderStates states);
	virtual char inputHandler()  override;
	virtual void exitScene()  override;
	virtual void closeScene()  override;
	virtual void loadScene(scene*)  override;


protected:


private:
	Square chara;
	Square enemy;
	Square background;
	sprite* menu[10];

};