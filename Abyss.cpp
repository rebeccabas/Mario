#include "Abyss.h"



Abysss::Abysss()
{
	file = "abyss.jpg";

	try
	{
		if (!texture.loadFromFile("assets/image/" + file))
		{
			throw - 1;
		}
	}
	catch (int)
	{
		std::cout << "Error: Cannot load abyss texture.";
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


Abysss::~Abysss()
{
}
