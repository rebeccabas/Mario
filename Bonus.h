#pragma once

#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include"entity.h"

using namespace sf;
class Bonus : public Entity
{
private:

public:
	Bonus() {};
	Bonus(sf::Vector2f startingPosition);
	~Bonus();
};
