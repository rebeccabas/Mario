#include "FlyTur.h"



FlyTur::FlyTur()
{
	file = "FlyTur.png";

	try
	{
		if (!texture.loadFromFile("assets/image/" + file))
		{
			throw - 1;
		}
	}
	catch (int)
	{
		std::cout << "Error: Cannot load FlyTur texture";
		exit(1);
	}

	sprite.setTexture(texture);

	Height = 48;
	Width = 32;
	Velocity = 0.2;
	velocity = { Velocity , 0 };
	sprite.setOrigin(Width / 2.f, Height / 2.f);

	isFriendly = false;
}


FlyTur::~FlyTur()
{
}
