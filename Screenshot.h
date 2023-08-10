#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>

#include<ctime>
#include<string>
#include<algorithm>
#include<iostream>
class Screenshot
{
	time_t czas;	// time in seconds count from 1970 year
	std::string localData;	// time in standard format example "Thu Jan 01 01:00:00 1970"
	std::string fileExtension = ".png";
public:
	Screenshot();
	~Screenshot();
	void create(sf::RenderWindow* window);
	void removeSpace(std::string& text);
};

