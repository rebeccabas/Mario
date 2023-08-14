#pragma once
#include "SFML/Graphics.hpp"
#include "Mario.h"
#include<iostream>
#include<fstream>
#include <algorithm>    
#include <vector>       

#define MAX_NUMBER_OF_ITEMS 4
#define NUMBER_OF_RESULTS 3
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 512


class result {
public:
	std::string date;
	std::string score;
	std::string time;
	std::string coins;
	std::string userName;
	result(std::string date, std::string score, std::string time, std::string coins, std::string userName) :date(date), score(score), time(time), coins(coins), userName(userName) {};
};

class Menu
{
private:
	Mario mario;
	sf::View view;
	bool isOn = true;
	int selectedItemIndex = 0;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];

	std::vector<result> loadedResults;
	sf::Text resultsToDisplay[NUMBER_OF_RESULTS];


public:
	Menu();
	~Menu();

	Sprite loadResources(sf::RenderWindow& window, Sprite spriteBackground);
	void followMario(int center);
	void draw(sf::RenderWindow& window, int center);
	void drawMenuBackground(sf::RenderWindow& window, int center);
	void drawBestResults(sf::RenderWindow& window, int center);
	void drawResults(sf::RenderWindow& window, int center);
	void drawBestResultsBackground(sf::RenderWindow& window, int center);
	void MoveUp();
	void MoveDown();
	int GetPressedItem();
	void setPressedItem(int item);
	bool isON();
	void setIsON(bool status);
	void readResultsFromFile();
	void loadReslutsToArray();
	static bool comparator(result i1, result i2);
	void sortResults();

	void gameWon(int center, sf::RenderWindow& window);
	void reset();
};
