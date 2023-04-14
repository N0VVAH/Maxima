#pragma once
#include "SFML/Audio.hpp"
#include <vector>


class soundBase : public sf::Sound
{
public:
	soundBase(const char* n, uint32_t i, const char* path);
	const char* name;
	uint32_t id;

protected:
	sf::SoundBuffer sound;
};

class soundEffect : soundBase
{
public:
	soundEffect(const char* n, uint32_t i, const char* path) : soundBase(n, i, path) {};

};

class Music : soundBase
{
public:
	Music(const char* n, uint32_t i, const char* path) : soundBase(n, i, path) {};
	inline sf::SoundBuffer getBuffer() { return sound; }

};

class SoundsController
{
public:
	static std::vector<soundBase*> sounds;
	static void init();
	static void playSound(int id, bool loop);
	static Music* getMusic(uint32_t id);

private:
	//variables
	static sf::Sound musicPlayer;
};