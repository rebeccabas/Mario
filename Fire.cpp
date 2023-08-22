#include "Fire.h"



Fireee::Fireee()
{
	file = "fire-1.jpg";

	try
	{
		if (!texture.loadFromFile("assets/image/" + file))/*, sf::IntRect(0, 0, Height, Width)))*/
		{
			throw - 1;
		}
	}
	catch (int)
	{
		std::cout << "Error: Cannot load fire texture.";
		exit(1);
	}

	sprite.setTexture(texture);


	Height = 60;
	Width = 55;
	Velocity = 0.0;
	velocity = { Velocity ,0 };
	sprite.setOrigin(Width / 2.f, Height / 2.f);

	isFriendly = false;
	killable = false;
}


Fireee::~Fireee()
{
}
