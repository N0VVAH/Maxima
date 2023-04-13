#include "item.h"

std::vector<item*> ItemManager::items;


item::item(uint32_t i, const char* n, const char* path) : id(i), name(n)
{
	if (path == NULL)
	{
		icon.loadFromFile("..\\assets\\images\\MISSING.png");
	}
	else
	{
		icon.loadFromFile(path);
	}
}

ItemManager::ItemManager()
{
	items.resize(32);

	items[0] = (new item(0, "test"));
	items[1] = (new item(1, "BasicSword", "..\\assets\\images\\icons\\basicsword.png"));
	items[2] = (new item(2, "Slime Chunk", "..\\assets\\images\\icons\\slimeChunk.png"));
}

item* ItemManager::getItem(uint32_t id)
{
	if (items[id]->id == id)
	{
		return items[id];
	}

	for (size_t i = 0; i < items.size(); i++)
	{
		if (items[i]->id == id)
		{
			return items[i];
		}
	}
}

sf::Texture* ItemManager::getTexture(uint32_t id)
{
	if (items[id]->id == id)
	{
		return &items[id]->icon;
	}

	for (size_t i = 0; i < items.size(); i++)
	{
		if (items[i]->id == id)
		{
			return &items[i]->icon;
		}
	}
}