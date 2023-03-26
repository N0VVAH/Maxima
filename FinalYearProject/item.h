#pragma once
#include <cstdint>
#include <vector>

class item
{
public:
	item(uint32_t i, const char* n) : id(i), name(n) {}
	uint32_t id;
	const char* name;

private:



};

class ItemManager
{
public:
	ItemManager();
	item* getItem(uint32_t id);

private:
	std::vector<item> items;

};