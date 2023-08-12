#include "Mario.h"

Mario::Mario()
{

	file = "mario.png";

	try
	{
		if (!texture.loadFromFile("assets/" + file, sf::IntRect(0, 0, 64, 64)))
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
	startingPosition = { 62,200 };
	sprite.setPosition(startingPosition);
	Width = 32;
	Height = 60;
	Velocity = 0.4;
	sprite.setOrigin(Width / 2.f, Height / 2.f);



	jumpBuffer.loadFromFile(JUMP_SOUND);
	jumpSound.setBuffer(jumpBuffer);

	dieBuffer.loadFromFile(DIE_SOUND);
	dieSound.setBuffer(dieBuffer);
}


void Mario::update(int mapWidth)
{
	this->sprite.move(this->velocity);

	if (Keyboard::isKeyPressed(Keyboard::Key::Left) && this->left() > 0)
		velocity.x = -Velocity;
	else if (Keyboard::isKeyPressed(Keyboard::Key::Right) && this->right() < mapWidth)
		velocity.x = Velocity;
	else
		velocity.x = 0;

	if (Keyboard::isKeyPressed(Keyboard::Key::Up) && canJump) {
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
		velocity.y = -(Velocity+0.3) * (1 - (jumpCurrentPosition * 1.4) / jumpHeight);
	}
	else
	{
		jumpCurrentPosition = 0;
		velocity.y = 0.4;
		canJump = false;
		keyRel = false;
	}

	if (this->bottom() > WINDOW_HEIGHT)//mario falling off
	{
	
		//twice, Mario can be in 2 lives mode, but this should kill him anyway
		this->dead();
		this->dead();

		goToStart();

	}
}


void drawDeathScreen(int center, sf::RenderWindow& window)
{
	sf::Texture texture;
	try {
		if (!texture.loadFromFile("assets/deathscreen.png"))
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
		sprite.setScale(1.3, 1);
		Width *= 1.3;
	}
	else
	{
		sprite.setScale(32 / Width, 1);
		Width = 32;
	}
}

void Mario::dead() {

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
			dieSound.play();
			lives = 3;
			isAlive = false;
			//Game game;
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