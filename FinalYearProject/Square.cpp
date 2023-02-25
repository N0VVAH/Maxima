#include "square.h"
#include "iostream"

Square::Square(sf::Color colour, int xSize, int ySize)
{
	shape = sf::RectangleShape();
	shape.setOrigin(xSize / 2, ySize / 2);
	shape.setSize(sf::Vector2f{ xSize * 1.0f, ySize * 1.0f });
	shape.setFillColor(colour);
}

Square::Square(sf::Color colour)
{
	shape = sf::RectangleShape();
	shape.setSize({ 10, 10 });
	shape.setFillColor(colour);
	shape.setOrigin(5, 5);
}

Square::Square(const char* path)
{
	shape = sf::RectangleShape();
	shape.setSize({ 10, 10 });

	try
	{
		texture.loadFromFile(path);
	}
	catch (const std::exception& e)
	{
		std::cout << "Error loading Texture for Square Sprite " << e.what() << "\n";
	}
	shape.setOrigin(5, 5);
	shape.setTexture(&texture);
}

Square::Square(const char* path, int xSize, int ySize)
{
	shape = sf::RectangleShape();
	shape.setSize({(float)xSize, (float)ySize});

	try
	{
		texture.loadFromFile(path);
	}
	catch (const std::exception& e)
	{
		std::cout << "Error loading Texture for Square Sprite " << e.what() << "\n";
	}
	shape.setOrigin(xSize / 2, ySize / 2);
	shape.setTexture(&texture);
}

Square::Square(const char* path, sf::IntRect rect)
{
	shape = sf::RectangleShape();
	shape.setSize({ 10, 10 });

	try
	{
		texture.loadFromFile(path);
	}
	catch (const std::exception& e)
	{
		std::cout << "Error loading Texture for Square Sprite " << e.what() << "\n";
	}

	shape.setTexture(&texture);
	shape.setTextureRect(rect);

}

void Square::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape, states);
}

void* Square::onClick()
{
	return nullptr;
}

void Square::setClick(void*)
{

}

void Square::setPos(float xPos, float yPos)
{
	shape.setPosition({ xPos, yPos });
}

void Square::movePos(float xOffset, float yOffset)
{
	shape.move({xOffset, yOffset});
}

void Square::changeMapping(sf::IntRect rect)
{
	shape.setTextureRect(rect);
}
