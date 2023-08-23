#pragma once
#include"tileMap.h"
#include"Entity.h"
#include"Mario.h"
#include"Turtle.h"
#include"GameInfo.h"
#include "Menu.h"
#include"Bonus.h"
#include"Spikey.h"
#include"flyTur.h"
#include"Plant1.h"
#include "Abyss.h"
#include"Plant2.h"

#include<Windows.h>
#include<iostream>
#include<fstream>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 512
#define TOP 0
#define BOTTOM 1
#define LEFT 2
#define RIGHT 3
#define END_GAME 9
#define MUSHROOM_SOUND "assets/sound/mushroom.wav"
#define STOMP_SOUND "assets/sound/stomp.wav"

class Game
{
	Mario mario;
	std::vector<Entity> mobs;
	TileMap map;
	GameInfo gameInfo;
	Menu menu;

	
	sf::Event sfEvent;

	DWORD currentTickCount;
	DWORD lastDrawTickCount;


	SoundBuffer mushroomBuffer, stompBuffer;
	Sound mushroomSound, stompSound;

	bool won = false;

public:
	sf::RenderWindow* window;
	sf::View view;
	friend class Mario;
	// constructors/destructors
	Game();
	virtual ~Game();

	// functions
	void intersection(Mario& mario, Entity& entity);
	void updateSFMLEvents();
	void update();
	void render();
	void run();
	void Menu(int center);
	void cameraMovement();
	void repairSFMLTextures();
	void drawMobs();
	void Bonuses();
	void addMobs();

};

