#pragma once
#include <cstdint>
#include <vector>
#include "SFML/Graphics.hpp"

class item
{
public:
	item() {};
	item(uint32_t i, const char* n, const char* path = NULL);
	uint32_t id;
	const char* name;
	sf::Texture icon;

private:



};

class ItemManager
{
public:
	ItemManager();
	static item* getItem(uint32_t id);
	static sf::Texture* getTexture(uint32_t id);

private:
	static std::vector<item*> items;

};