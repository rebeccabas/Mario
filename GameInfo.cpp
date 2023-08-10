#include "GameInfo.h"
#pragma warning(disable : 4996)

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 512


GameInfo::GameInfo()
{
	try
	{
		if (!font.loadFromFile("assets/PixeloidSans.ttf"))
		{
			throw - 1;
		}
	}
	catch (int)
	{
		std::cout << "can not load mario texture";
		exit(1);
	}

	info[0].setFont(font);
	info[0].setFillColor(sf::Color::White);
	info[0].setCharacterSize(36);
	info[0].setString("COINS: " + std::to_string(coins));


	info[1].setFont(font);
	info[1].setFillColor(sf::Color::White);
	info[1].setCharacterSize(36);
	info[1].setString("SCORE: " + std::to_string(score));


	info[2].setFont(font);
	info[2].setFillColor(sf::Color::White);
	info[2].setCharacterSize(36);
	info[2].setString("TIME: ");

	info[3].setFont(font);
	info[3].setFillColor(sf::Color::White);
	info[3].setCharacterSize(36);
	info[3].setString("LIVES: " + std::to_string(lives));
}


GameInfo::~GameInfo()
{
}

void GameInfo::followMario(int center)
{
	info[0].setPosition(sf::Vector2f(center - 430, WINDOW_HEIGHT / 20));
	info[1].setPosition(sf::Vector2f(center - 100, WINDOW_HEIGHT / 20));
	info[2].setPosition(sf::Vector2f(center + 100, WINDOW_HEIGHT / 20));
	info[3].setPosition(sf::Vector2f(center + 300, WINDOW_HEIGHT / 20));
}


void GameInfo::draw(sf::RenderWindow& window, int center)
{
	//display option to choose
	for (int i = 0; i < NUMBER_OF_ITEMS; i++)
	{
		window.draw(info[i]);
	}
}

void GameInfo::reset()
{
	coins = 0;
	time = 0;
	score = 0;
	info[0].setString("COINS: " + std::to_string(coins));
	info[1].setString("SCORE: " + std::to_string(score));

	finish = start = std::chrono::high_resolution_clock::now();

}

void GameInfo::showLife()
{
	lives--;
	if (lives <= 0) { resetLife(); }
	info[3].setString("LIVES: " + std::to_string(lives));
}

int GameInfo::getLife()
{
	//info[3].setString("LIVES: " + std::to_string(lives + 1));
	return lives;
}

void GameInfo::resetLife()
{
	lives = 3;
}

void GameInfo::increaseCoins()
{
	coins++;
	increaseScoreCoins();
	info[0].setString("COINS: " + std::to_string(coins));
}

void GameInfo::increaseScoreBonus()
{
	score += 50;
	info[1].setString("SCORE: " + std::to_string(score));
}

void GameInfo::increaseScoreCoins()
{
	score += 10;
	info[1].setString("SCORE: " + std::to_string(score));
}

void GameInfo::countTime()
{
	finish = std::chrono::high_resolution_clock::now();
	difference = (int)((finish - start).count() / 1000000000);
	if (switcher != difference)
	{
		time++;
		start = std::chrono::high_resolution_clock::now();
	}

	info[2].setString("TIME: " + std::to_string(time));
}

void GameInfo::saveResultToFile()
{
	typeUserName();
	score = score - (time * 5);
	if (score < 0)
		score = 0;
	std::time(&czas);
	localData = ctime(&czas);

	std::ofstream myfile;
	myfile.open("../results/Results.txt", std::ios::app);
	myfile << localData << "Coins: " << properFormat3(coins) << " Score: " << properFormat4(score) << " Time: " << properFormat3(time) << " " << userName << std::endl << std::endl;
	myfile.close();
}

std::string GameInfo::properFormat3(int number) // return 3 numbers 3 -> 003, 49 -> 049, 234 -> 234
{
	if (number < 10)
		return "00" + std::to_string(number);
	else if (number < 100)
		return "0" + std::to_string(number);
	else
		return std::to_string(number);
}
std::string GameInfo::properFormat4(int number) // return 4 numbers 3 -> 0003, 49 -> 0049, 234 -> 0234
{
	if (number < 10)
		return "000" + std::to_string(number);
	else if (number < 100)
		return "00" + std::to_string(number);
	else if (number < 1000)
		return "0" + std::to_string(number);
	else
		return std::to_string(number);
}
void GameInfo::typeUserName()
{
	bool correctName = false;
	std::string userName;
	std::regex nameTemplate("^[a-zA-Z]+(([',. -][a-zA-Z ])?[a-zA-Z]*)*$");
	system("CLS");
	std::cout << "Enter your name " << std::endl;

	while (!correctName)
	{
		std::cin.clear();
		std::cin >> userName;
		if (std::regex_match(userName, nameTemplate))
		{
			correctName = true;
		}
		else
		{
			std::cout.clear();
			system("CLS");
			std::cout << "Type name again, only letters are ok" << std::endl;
		}
	}
	this->userName = userName;
}
