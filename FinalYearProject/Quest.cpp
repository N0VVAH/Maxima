#include "quest.h"


void Quest::init()
{
	quests = "Quest:\n";
	textProps p;
	p.string = quests.c_str();
	p.col = sf::Color::White;
	p.fontSize = 30;

	toDisplay = new Text(p);

	toDisplay->setPos(1240, 200);

}

void Quest::render(sf::RenderTarget& target, sf::RenderStates states)
{
	toDisplay->draw(target, states);
}

void Quest::setQuest(std::string quest)
{
	if (quests.size() > 10)
	{
		return;
	}
	quests.append(quest);
	toDisplay->changeText(quests.c_str());
}

void Quest::removeAllQuests()
{
	quests = "Quest\n";
	toDisplay->changeText(quests.c_str());
}
