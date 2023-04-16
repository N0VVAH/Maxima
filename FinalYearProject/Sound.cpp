#include "sound.h"
#include <iostream>

std::vector<soundBase*> SoundsController::sounds = std::vector<soundBase*>();
sf::Sound SoundsController::musicPlayer = sf::Sound();

void SoundsController::init()
{
	//sounds.reserve(16);

	//sounds.push_back((soundBase*)(new Music("MainMenu Music", 0, "..\\assets\\sounds\\music\\mainmenu.flac")));
}

void SoundsController::playSound(int id, bool loop)
{
	if (musicPlayer.Playing == false)
	{
		musicPlayer.setBuffer(getMusic(id)->getBuffer());
		musicPlayer.setLoop(loop);
		musicPlayer.play();
		return;
	}

}

Music* SoundsController::getMusic(uint32_t id)
{
	if (sounds[id]->id == id)
	{
		return (Music*)sounds[id];
	}

	for (int i = 0; i < sounds.size(); i++)
	{
		if (sounds[i]->id == id)
		{
			return (Music*)sounds[i];
		}
	}
}

soundBase::soundBase(const char* n, uint32_t i, const char* path) : name(n), id(i)
{
	sound = sf::SoundBuffer();
	try
	{
		sound.loadFromFile(std::string(path));
	}
	catch (const std::exception& e)
	{
		std::cout << "ERROR LOADING SOUND FILE " << e.what() << "\n";
	}
}

