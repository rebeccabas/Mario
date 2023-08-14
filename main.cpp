#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include <iostream>
#include "Game.h"

int main()
{
	Game game;
	sf::SoundBuffer buffer;
	sf::Sound bgsound;

	if (!buffer.loadFromFile("assets/bgm.wav")) {
		//error handling
		std::cout << "can't find sound file" << std::endl;
	}
	bgsound.setBuffer(buffer);

	if (bgsound.getStatus() != sf::Sound::Playing) {
		bgsound.play();

	}
	game.run();
	/*
	// Create a v	ideo mode object
	VideoMode vm(1920, 1080);

	// Create and open a window for the game
	RenderWindow window(vm, "Timber!!!");

	// Create a texture to hold a graphic on the GPU
	Texture texture;
	texture.loadFromFile("assets/turtle.png"), sf::IntRect(0, 0, 32, 32);

	// Create a sprite
	Sprite spriteBackground;

	// Attach the texture to the sprite
	spriteBackground.setTexture(texture);

	// Set the spriteBackground to cover the screen
	spriteBackground.setPosition(0, 0);


	while (window.isOpen())
	{



		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}



		
	
		

		// Clear everything from the last frame
		window.clear();

		// Draw our game scene here
		window.draw(spriteBackground);

		// Show everything we just drew
		window.display();


	}*/

	return 0;
}