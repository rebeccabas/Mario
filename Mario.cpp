#include "Mario.h"
#include "GameInfo.h"
#include <stdlib.h>
#include <math.h>
#define _WIN32_WINNT 0x0500

#include <windows.h>

Mario::Mario()
{

	file = "stationary-right-01.png";

	try
	{
		if (!texture.loadFromFile("assets/image/" + file, sf::IntRect(0, 0, 64, 64)))
		{
			throw - 1;
		}
	}
	catch (int)
	{
		std::cout << "Error: Cannot load Mario texture.";
		exit(1);
	}

 

	sprite.setTexture(texture);
	startingPosition = {950,0 };
	sprite.setPosition(startingPosition);
	Width = 32;
	Height = 60;
	Velocity = 0.5;
	sprite.setOrigin(Width / 2.f, (Height / 2.f)+4);

	jumpBuffer.loadFromFile(JUMP_SOUND);
	jumpSound.setBuffer(jumpBuffer);

	dieBuffer.loadFromFile(DIE_SOUND);
	dieSound.setBuffer(dieBuffer);

	hitBuffer.loadFromFile(HIT_SOUND);
	hitSound.setBuffer(hitBuffer);
}

void Mario::update(int mapWidth)
{
	this->sprite.move(this->velocity);

	if (Keyboard::isKeyPressed(Keyboard::Key::Left) && this->left() > 0)
	{
		if (!bigMario)
			file = "walk-left-01.png";
		else
			file = "big-walk-left-01.png";

		try
		{
			if (!texture.loadFromFile("assets/image/" + file, sf::IntRect(0, 0, 64, 64)))
			{
				throw - 1;
			}
		}
		catch (int)
		{
			std::cout << "Error: Cannot load Mario texture.";
			exit(1);
		}
		sprite.setTexture(texture);
		velocity.x = -Velocity + 0.2; // Adjusted leftward velocity while jumping
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Right) && this->right() < mapWidth)
	{
		if (!bigMario)
			file = "walk-right-01.png";
		else
			file = "big-walk-right-01.png";

		try
		{
			if (!texture.loadFromFile("assets/image/" + file, sf::IntRect(0, 0, 64, 64)))
			{
				throw - 1;
			}
		}
		catch (int)
		{
			std::cout << "Error: Cannot load Mario texture.";
			exit(1);
		}
		sprite.setTexture(texture);
		velocity.x = Velocity - 0.2; // Adjusted rightward velocity while jumping
	}
	else 
	{
		velocity.x = 0.0f;
		
	}
	

	if (Keyboard::isKeyPressed(Keyboard::Key::Up) && canJump)
	{
		if (!bigMario)
			file = "jump-left-01.png";
		else
			file = "big-jump-left-01.png";

		try
		{
			if (!texture.loadFromFile("assets/image/" + file, sf::IntRect(0, 0, 64, 64)))
			{
				throw - 1;
			}
		}
		catch (int)
		{
			std::cout << "Error: Cannot load Mario texture.";
			exit(1);
		}
		sprite.setTexture(texture);
		keyRel = true;
		jumpSound.play();
	}

	if (keyRel && this->top() > 0 && canJump)
	{
		if (jumpCurrentPosition > jumpHeight)
		{
			jumpCurrentPosition = 0;
			canJump = false;
			keyRel = false;
		}
		jumpCurrentPosition++;

		velocity.y = -(Velocity) * (0.95 - (jumpCurrentPosition * 1.4) / jumpHeight); // Adjusted upward jump velocity
	}
	else
	{
		jumpCurrentPosition = 0;
		velocity.y = 0.55f; // Adjusted falling velocity
		canJump = false;
		keyRel = false;
	}
	if (this->bottom() > WINDOW_HEIGHT)//mario falling off
	{
		this->dead();
		//goToStart();

	}
}


void drawDeathScreen(int center, sf::RenderWindow& window)
{
	sf::Texture texture;
	try {
		if (!texture.loadFromFile("assets/image/deathscreen.png"))
		{
			throw - 1;
		}
	}
	catch (int)
	{
		std::cout << "can not load death background texture";
		exit(1);
	}
	//display background
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setOrigin({ 0,0 });
	sprite.setPosition(0,0);
	window.draw(sprite);
}

void Mario::goToStart()
{
	this->sprite.setPosition(startingPosition);
}
void Mario::killingMove()
{
	this->sprite.move({ 0,-40 });
}

void Mario::setCanJump(bool canJump)
{
	this->canJump = canJump;
}

bool Mario::isBig()
{
	return bigMario;
}

void Mario::setBigMario(bool isBig)
{

	if (bigMario = isBig)
	{
		file = "big-stationary-right-01.png";

		try
		{
			if (!texture.loadFromFile("assets/image/" + file, sf::IntRect(0, 0, 64, 64)))
			{
				throw - 1;
			}
		}
		catch (int)
		{
			std::cout << "Error: Cannot load big Mario texture.";
			exit(1);
		}
		sprite.setTexture(texture);

		//sprite.setScale(1.3, 1);
		//Width *= 1.3;
	}
	else
	{
		file = "stationary-right-01.png";

		try
		{
			if (!texture.loadFromFile("assets/image/" + file, sf::IntRect(0, 0, 64, 64)))
			{
				throw - 1;
			}
		}
		catch (int)
		{
			std::cout << "Error: Cannot load big Mario texture.";
			exit(1);
		}
		sprite.setTexture(texture);
		//sprite.setScale(32 / Width, 1);
		//Width = 32;
	}
}

void Mario::dead() {
	hitSound.play();
	if (bigMario) {
		setBigMario(false);
		reset();
	}
	else
	{
		lives--;
		if (lives > 0)
		{
			reset();
		}
		else
		{
			GameInfo gameInfo;

			dieSound.play();

			sf::RenderWindow window(sf::VideoMode(1024, 512), "GAME OVER");

			// run the program as long as the window is open
			while (window.isOpen())
			{

				sf::Texture backgroundTexture;
				try {
					if (!backgroundTexture.loadFromFile("assets/image/deathscreen.png"))
					{
						throw - 1;
					}
				}
				catch (int)
				{
					std::cout << "Error: Cannot load death background texture.";
					exit(1);
				}
				//display background
				sf::Sprite spriteBackground;
				spriteBackground.setTexture(backgroundTexture);
				spriteBackground.setPosition(0, 0);
				window.draw(spriteBackground);
				window.display();
				// check all the window's events that were triggered since the last iteration of the loop
				sf::Event event;

				if(Keyboard::isKeyPressed(Keyboard::Enter))
				{
					HWND hwnd = GetConsoleWindow();
					SetForegroundWindow(hwnd);
					SetActiveWindow(hwnd);
					
					gameInfo.saveResultToFile();
					window.close();
				}
				while (window.pollEvent(event))
				{
					// "close requested" event: we close the window
					if (event.type == sf::Event::Closed)
						window.close();
				}

				
			}

			isAlive = false;

			lives = 3;
			
		}
	}
}


float Mario::getCurrentTime()
{
	return clock.getElapsedTime().asMilliseconds();
}
void Mario::fallDown()
{
	this->keyRel = false;
}