#pragma once

#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include"entity.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 512

using namespace sf;
class Spikey : public Entity
{
private:

public:
	Spikey();
	~Spikey();

};
