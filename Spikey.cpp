#include "Spikey.h"



Spikey::Spikey()
{
	file = "Spikey.png";
	try
	{
		if (!texture.loadFromFile("assets/" + file))/*, sf::IntRect(0, 0, Height, Width)))*/
		{
			throw - 1;
		}
	}
	catch (int)
	{
		std::cout << "Error: Cannot load Spikey texture.";
		exit(1);
	}

	sprite.setTexture(texture);

	Height = 32;
	Width = 32;
	Velocity = 0.1;
	velocity = { Velocity ,Velocity };
	sprite.setOrigin(Width / 2.f, Height / 2.f);

	isFriendly = false;
	killable = false;
}


Spikey::~Spikey()
{
}
