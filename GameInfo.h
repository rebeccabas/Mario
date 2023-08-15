#pragma once
#include "SFML/Graphics.hpp"
#include<SFML/Window.hpp>
#include "Mario.h"
#include <chrono>
#include<iostream>
#include<fstream>
#include<ctime>
#include<algorithm>
#include<regex>

#define NUMBER_OF_ITEMS 4
class GameInfo
{
	int coins = 0;
	int time = 0;
	int score = 0;
	Mario mario;

	sf::Font font;
	sf::Text info[NUMBER_OF_ITEMS];

	// time in game
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point finish;
	bool difference;
	bool switcher = 0;

	// save to file
	time_t czas;	// time in seconds count from 1970 year
	std::string localData;	// time in standard format example "Thu Jan 01 01:00:00 1970"
	std::string fileExtension = ".png";

	std::string userName;
public:
	friend class Mario;
	friend class Game;
	GameInfo();
	~GameInfo();

	void followMario(int center);
	void draw(sf::RenderWindow& window, int center);
	void showLife2();
	void showLife1();
	int getLife();
	void reset();

	void increaseCoins();
	void increaseScoreBonus();
	void increaseScoreCoins();
	void countTime();


	void saveResultToFile();

	std::string properFormat3(int number); // return 3 numbers 3 -> 003, 49 -> 049, 234 -> 234
	std::string properFormat4(int number); // return 4 numbers 3 -> 0003, 49 -> 0049, 234 -> 0234

	void typeUserName();
};
