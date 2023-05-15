#pragma once
#include "text.h"

class Quest
{

public:
	static void init();
	static void render(sf::RenderTarget& target, sf::RenderStates states);
	static void setQuest(std::string quest);
	static void removeAllQuests();

	static std::string quests;
private:

	static Text* toDisplay;

};