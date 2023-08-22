#include "Bonus.h"

Bonus::Bonus(sf::Vector2f startingPosition)
{
	file = "bonus.png";

	try
	{
		if (!texture.loadFromFile("assets/image/" + file))/*, sf::IntRect(0, 0, Height, Width))*/
		{
			throw - 1;
		}
	}
	catch (int)
	{
		std::cout << "Error: Cannot load bonus texture.";
		exit(1);
	}

	sprite.setTexture(texture);
	this->startingPosition = startingPosition;
	sprite.setPosition(startingPosition);

	Height = 32;
	Width = 32;
	Velocity = 0.1;
	velocity = { Velocity ,2 * Velocity };
	sprite.setOrigin(Width / 2.f, Height / 2.f);

	isFriendly = true;
}


Bonus::~Bonus()
{
}
