#include "scene.h"

void scene::draw(sf::RenderTarget& target, sf::RenderStates states)
{
	for (size_t i = 0; i < render.size(); i++)
	{
		render[i]->draw(target, states);
	}

	for (size_t i = 0; i < UI.size(); i++)
	{
		UI[i]->draw(target, states);
	}
}