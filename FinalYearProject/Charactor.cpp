#include "Charactor.h"
#include "iostream"

void Charactor::CharSetup(const char* path, int xSize, int ySize)
{
	chara = new sf::RectangleShape();
	try
	{
		texture.loadFromFile(path);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
	}

	chara->setSize({ (float)xSize, (float)ySize });
	chara->setTexture(&texture);
	lastpos = sf::Vector2f{ 50, 50 };
	type = 'c';
}

void Charactor::CharSetup(sf::Color colour)
{
	chara = new sf::RectangleShape();
	chara->setSize({ 50, 50 });
	chara->setFillColor(colour);
	lastpos = sf::Vector2f{ 50, 50 };
	type = 'c';
}

void Charactor::CharSetup(sf::Color colour, float x, float y)
{
	chara = new sf::RectangleShape();
	chara->setOrigin(25, 25);
	chara->setSize({ x, y });
	chara->setFillColor(colour);
	lastpos = sf::Vector2f{ 50, 50 };
	type = 'c';
}

void Charactor::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*chara, states);
}

void Charactor::update(float timestep)
{
	if (textureAtlas == true)
	{
		timeSinceLastTexture += timestep;

		if (timeBetween <= timeSinceLastTexture)
		{
			if (curAtlasTexture + 1 == texturesInAtlas)
			{
				curAtlasTexture = 0;
				uvStart = sf::Vector2f(0.0f, 0.0f);
			}
			else
			{
				curAtlasTexture++;
				uvStart.x += uvSize.x;
			}

			timeSinceLastTexture = 0.0f;

			chara->setTextureRect(sf::IntRect(uvStart.x, uvStart.y, uvSize.x, uvSize.y));

		}
	}
}

void Charactor::updateTexture()
{
	chara->setTextureRect(sf::IntRect(uvStart.x, uvStart.y, uvSize.x, uvSize.y));
}

void* Charactor::onClick()
{
	return nullptr;
}

void Charactor::setClick(void*)
{

}

void Charactor::setPos(float xPos, float yPos)
{
	chara->setPosition({ xPos, yPos });
	lastpos = sf::Vector2f{ xPos, yPos };
}

void Charactor::movePos(float xOffset, float yOffset)
{
	lastpos = chara->getPosition();
	chara->move({ xOffset, yOffset });
}
