#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<iostream>

using namespace sf;
class Entity : public Drawable // Drawable makes possible to use window.draw(Ball)
{
	public:
	Texture texture;
	Sprite sprite;
	float Width;
	float Height;
	float Velocity;

	Vector2f startingPosition;
	Vector2f velocity{ Velocity, Velocity };

	void draw(RenderTarget& target, RenderStates state) const; // to use window.draw(Ball)

	bool destroyMode = 0;
	bool isFriendly = 0;
	bool killable = true;


	sf::VertexArray m_vertices;
	sf::Texture m_texture;

	std::string file;

public:
	Entity() {};

	~Entity() = default;

	Vector2f getPosition();

	void setPosition(Vector2f position);


	void update();

	float left();
	float right();
	float top();
	float bottom();

	void moveLeft();
	void moveRight();
	void moveTop();
	void moveBottom();

	bool isAlive = true;

	void MovingDirectiongLeft() { velocity.x = -Velocity; }
	void MovingDirectiongRight() { velocity.x = Velocity; }

	Sprite getSprite() { return sprite; }

	void dead() { isAlive = false; }
	void deadAtOnce() { isAlive = false; }
	bool getIsAlive() { return isAlive; }
	bool getDestroyMode() { return destroyMode; }
	void reset();
	bool getIsFriendly() { return isFriendly; }

	void repair();
	bool isKillable() { return killable; }
};


