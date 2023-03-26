#pragma once
#include "square.h"


class scene
{
public:
	scene() {};
	virtual void update(sf::RenderWindow* window, float dtime) = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states);
	virtual char inputHandler() = 0;
	virtual void exitScene() = 0;
	virtual void closeScene() = 0;
	virtual void loadScene(scene*) = 0;
	bool removeFromRender(sprite* toRemove)
	{
		for (size_t i = 0; i < render.size(); i++)
		{
			if (render[i] == toRemove)
			{
				render.erase(render.begin() + i);
				return true;
			}
		}

		return false;
	};

	bool removeFromUI(sprite* toRemove)
	{
		for (size_t i = 0; i < UI.size(); i++)
		{
			if (UI[i] == toRemove)
			{
				UI.erase(UI.begin() + i);
				return true;
			}
		}

		return false;
	};

	void sceneClean()
	{
		for (size_t i = 0; i < render.size(); i++)
		{
			if (render[i]->getPos() == sf::Vector2f(-400, -400))
			{
				delete render[i];
				i--;
			}
		}
	}

protected:
	std::vector<sprite*> render;
	std::vector<sprite*> UI;

	sf::Vector2i mouseDownPos;
	sf::Vector2i mouseUpPos;

	scene* prevScene;


};