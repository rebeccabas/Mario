#include "entity.h"


void Entity::draw(RenderTarget& target, RenderStates state)const
{
	target.draw(this->sprite, state);
}

Vector2f Entity::getPosition()
{
	return sprite.getPosition();
}

void Entity::setPosition(Vector2f position)
{
	startingPosition = position;
	sprite.setPosition(position);
}

void Entity::update()
{
	this->sprite.move(this->velocity);
}

float Entity::left()
{
	return this->sprite.getPosition().x - Width / 2.f;
}
float Entity::right()
{
	return this->sprite.getPosition().x + Width / 2.f;
}
float Entity::top()
{
	return this->sprite.getPosition().y - Height / 2.f;
}
float Entity::bottom()
{
	return this->sprite.getPosition().y + Height / 2.f;
}

void Entity::moveLeft()
{
	this->sprite.move(sf::Vector2f(-1, 0));
}
void Entity::moveRight()
{
	this->sprite.move({ 1,0 });
}
void Entity::moveTop()
{
	this->sprite.move({ 0,-1 });
}
void Entity::moveBottom()
{
	this->sprite.move({ 0,1 });
}

void Entity::reset()
{
	sprite.setPosition(startingPosition);
	isAlive = true;
}

void Entity::repair() {
	if (!texture.loadFromFile("assets/" + file, sf::IntRect(0, 0, Height, Width)))
	{
		std::cout << "Error: Texture did not load." << std::endl;
	}

	sprite.setTexture(texture);
}