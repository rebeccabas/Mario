#include "Screenshot.h"
#pragma warning(disable : 4996)


Screenshot::Screenshot()
{
}


Screenshot::~Screenshot()
{
}
void Screenshot::create(sf::RenderWindow* window)
{
	sf::Vector2u windowSize = window->getSize();
	sf::Texture texture;
	texture.create(windowSize.x, windowSize.y);
	texture.update(*window);
	sf::Image screenshot = texture.copyToImage();

	time(&czas);
	localData = ctime(&czas);

	removeSpace(localData);

	screenshot.saveToFile("../screenshots/" + localData + fileExtension);
}
void  Screenshot::removeSpace(std::string& text)
{
	text[3] = '_';
	text[7] = '_';
	text[8] = '_';
	text[10] = '_';
	text[13] = '.';
	text[16] = '.';
	text[19] = '_';
	text[24] = '_';
}