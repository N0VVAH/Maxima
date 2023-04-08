#include "item.h"

std::vector<item> ItemManager::items;


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

	items.push_back(item(0, "test"));
	items.push_back(item(1, "BasicSword", "..\\assets\\images\\icons\\basicsword.png"));
}

item* ItemManager::getItem(uint32_t id)
{
	if (items[id].id == id)
	{
		return new item(items[id]);
	}

	for (size_t i = 0; i < items.size(); i++)
	{
		if (items[i].id == id)
		{
			return new item(items[i]);
		}
	}
}