#include "item.h"

ItemManager::ItemManager()
{
	items.resize(32);

	//items.push_back(item(0, "test"));
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
			//return new item(items[i]);
		}
	}
}