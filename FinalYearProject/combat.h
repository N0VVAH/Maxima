#pragma once
#include "scene.h"
#include "globals.h"
#include "text.h"
#include "enemy.h"

class combat : public scene
{
public:
	combat(scene* prev, int* done, Enemy en);
	virtual void update(sf::RenderWindow* window, float dtime) override;
	//virtual void draw(sf::RenderTarget& target, sf::RenderStates states);
	virtual char inputHandler()  override;
	virtual void exitScene()  override;
	virtual void closeScene()  override;
	virtual void loadScene(scene*)  override;


protected:


private:
	//variables
	Enemy e;

	Text* PlayerStats;
	Text* name;
	Text* EnemyStats;
	Text* Ename;
	Text* historyText;

	std::string history[10];

	Square chara;
	Square enemy;

	Square background;

	Square rightMove;
	Square leftMove;
	sprite* menu[10];
	std::vector<sprite*> moves;

	char curDisplayed = 'n';

	int* doneFight;

	scene* PlayerDies;
	scene* PlayerWins;

	//functions
	void changeButtons(char butt);

	void moveSelected(move* playerMove);
	void playerBlocks();

	void addHsitory(const char* texty);
	void writeHistory();



};