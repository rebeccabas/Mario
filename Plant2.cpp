#include "Plant2.h"



Plant2::Plant2()
{
	file = "plant2.png";
	try
	{
		if (!texture.loadFromFile("assets/image/" + file))/*, sf::IntRect(0, 0, Height, Width)))*/
		{
			throw - 1;
		}
	}
	catch (int)
	{
		std::cout << "Error: Cannot load plant texture.";
		exit(1);
	}

	sprite.setTexture(texture);


	Height = 64;
	Width = 64;
	Velocity = 0.0;
	velocity = { Velocity ,Velocity };
	sprite.setOrigin(Width / 2.f, Height / 2.f);

	isFriendly = false;
	killable = false;
}


Plant2::~Plant2()
{
}