#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include <chrono>
#include <string>
#include"entity.h"
#include "Menu.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 512

#define JUMP_SOUND "assets/JUMP.wav"

using namespace sf;

class Mario : public Entity
{
private:
	int lives = 3;
	bool canJump = 0;
	float jumpHeight = 600;
	float jumpCurrentPosition = 0;
	std::chrono::steady_clock::time_point startTime;
	std::chrono::steady_clock::time_point finishTime;

	bool bigMario = false;
	std::string fileBigMario = "bigMario.png";

	sf::Clock clock;
	float flPreviousTime = 0;
	float flCurrentTime = 0;
	float dt;
	sf::View view;

	SoundBuffer jumpBuffer;
	Sound jumpSound;
	bool keyRel = false;

	Menu menuscreen;

public:
	Mario();

	void update(int mapWidth);

	void killingMove();
	void goToStart();

	void setCanJump(bool canJump);

	bool isBig();

	void setBigMario(bool isBig);

	void dead();

	float getCurrentTime();

	void fallDown();
	void drawDeathScreen();

};