#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

struct textureAtlasProps
{
	float timeSinceLastTexture = 0.0f;
	float timeBetween = 0.6f;
	uint32_t texturesInAtlas = 2;
	sf::Vector2f uvSize = sf::Vector2f(16.0f, 16.0f);
};


class sprite : public sf::Drawable
{
public:
	sprite() { } //default
	~sprite() 
	{
		if (data != nullptr)
		{
			data = (void*)int(0);
		}
		
	}
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	virtual void update(float timestep) {};
	virtual void updateTexture() {};
	virtual void* onClick() = 0;
	virtual void setClick(void*) = 0;
	inline virtual void setData(void* d) { data = d; }
	inline virtual void* getData() { return data; }
	virtual void setPos(float xPos, float yPos) = 0;
	virtual void movePos(float xOffset, float yOffset) = 0;
	virtual void setSize(float xOffset, float yOffset) {};
	virtual void setRotation(float rot) {}
	inline virtual sf::FloatRect getLocalBounds() { return sf::FloatRect(); }
	inline virtual sf::FloatRect getGlobalBounds() { return sf::FloatRect(); }
	inline virtual void changeText(const char* text) {}
	virtual void setFillColour(sf::Color colour) {};
	inline virtual sf::Vector2f getPos() { return sf::Vector2f(0.0f, 0.0f); }
	char type;

	inline void setTextureAtlas(textureAtlasProps p) 
	{
		textureAtlas = true;
		timeSinceLastTexture = p.timeSinceLastTexture;
		timeBetween = p.timeBetween;
		texturesInAtlas = p.texturesInAtlas;
		uvSize = p.uvSize;
	}
	inline bool getTextureAtlas() { return textureAtlas; }
	inline void setAtlasTileSize(sf::Vector2f size) { uvSize = size; }
	bool hasCollider = false;
	sf::RectangleShape Collider;
	virtual void setCollider(sf::Vector2f pos, sf::Vector2f size) {};

protected:
	void* data = nullptr;
	void (*Click)(void);

	sf::Texture texture;
	bool textureAtlas = false;
	float timeSinceLastTexture;
	float timeBetween;
	uint32_t texturesInAtlas;
	uint32_t curAtlasTexture = 0;
	sf::Vector2f uvStart;
	sf::Vector2f uvSize;
};