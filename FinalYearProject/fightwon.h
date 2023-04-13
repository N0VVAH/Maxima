#pragma once
#include "scene.h"
#include "globals.h"
#include "text.h"
#include "enemy.h"

class FightWon : public scene
{
public:
	FightWon(scene* prev, Enemy en);
	virtual void update(sf::RenderWindow* window, float dtime) override;
	//virtual void draw(sf::RenderTarget& target, sf::RenderStates states);
	virtual char inputHandler()  override;
	virtual void exitScene()  override;
	virtual void closeScene()  override;
	virtual void loadScene(scene*)  override;

	Enemy e;

private:
	Square done;
	Text* tDone;
	Square* items[20] = {};
	Text* Gold;
	Text* YourInv;
	Text* LootAbleItems;
};