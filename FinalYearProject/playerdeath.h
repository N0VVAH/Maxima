#pragma once
#include "scene.h"
#include "buttonSprite.h"
#include "text.h"


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

	Text* title;
	buttonSprite* quit;
	Text* quitText;
	buttonSprite* loadLastSave;
	Text* loadText;
	Square backGround = Square(sf::Color::White, 1600, 800);


};