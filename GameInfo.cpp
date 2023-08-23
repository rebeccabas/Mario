#include "GameInfo.h"
#pragma warning(disable : 4996)

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 512


GameInfo::GameInfo()
{
	try
	{
		if (!font.loadFromFile("assets/font/PixeloidSans.ttf"))
		{
			throw - 1;
		}
	}
	catch (int)
	{
		std::cout << "can not load font texture";
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
	info[3].setString("LIVES: " + std::to_string(mario.lives));
}


GameInfo::~GameInfo()
{
}

void GameInfo::followMario(int center)
{
	info[0].setPosition(sf::Vector2f(center - 430, WINDOW_HEIGHT / 20));
	info[1].setPosition(sf::Vector2f(center - 170, WINDOW_HEIGHT / 20));
	info[2].setPosition(sf::Vector2f(center + 90, WINDOW_HEIGHT / 20));
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
	info[3].setString("LIVES: " + std::to_string(mario.lives));

	finish = start = std::chrono::high_resolution_clock::now();

}

void GameInfo::showLife2()
{	
	info[3].setString("LIVES: " + std::to_string(2));
}

void GameInfo::showLife1()
{
	info[3].setString("LIVES: " + std::to_string(1));
}


int GameInfo::getLife()
{
	return mario.lives;
}

void GameInfo::increaseCoins()
{
	coins++;

	std::ofstream outputFile("results/coins.txt"); // Open the file for writing

	if (!outputFile.is_open()) {
		std::cerr << "Failed to open the output file." << std::endl;
	}

	outputFile << coins; // Write the value of time to the output file
	outputFile.close();  // Close the output file


	increaseScoreCoins();
	info[0].setString("COINS: " + std::to_string(coins));
}

void GameInfo::increaseScoreBonus()
{
	score += 50;

	std::ofstream outputFile("results/score.txt"); // Open the file for writing

	if (!outputFile.is_open()) {
		std::cerr << "Failed to open the output file." << std::endl;
	}

	outputFile << score; // Write the value of time to the output file
	outputFile.close();  // Close the output file


	info[1].setString("SCORE: " + std::to_string(score));
}

void GameInfo::increaseScoreCoins()
{
	score += 10;

	std::ofstream outputFile("results/score.txt"); // Open the file for writing

	if (!outputFile.is_open()) {
		std::cerr << "Failed to open the output file." << std::endl;
	}

	outputFile << score; // Write the value of time to the output file
	outputFile.close();  // Close the output file


	info[1].setString("SCORE: " + std::to_string(score));
}

void GameInfo::countTime()
{
	finish = std::chrono::high_resolution_clock::now();
	difference = (int)((finish - start).count() / 1000000000);
	if (switcher != difference)
	{
		time++;

		std::ofstream outputFile("results/time.txt"); // Open the file for writing

		if (!outputFile.is_open()) {
			std::cerr << "Failed to open the output file." << std::endl;
		}

		outputFile << time; // Write the value of time to the output file
		outputFile.close();  // Close the output file


		start = std::chrono::high_resolution_clock::now();
	}

	info[2].setString("TIME: " + std::to_string(time));
}

void GameInfo::saveResultToFile()
{
    typeUserName();
	std::cout << "Player: " << userName << std::endl;
    score = score - (time * 5);
    if (score < 0)
        score = 0;
    std::time(&czas);
    localData = ctime(&czas);

	int coinsf, timef, scoref;

	std::ifstream coinsFile("results/coins.txt"); // Open the file for reading
	if (!coinsFile.is_open()) {
		std::cerr << "Failed to open coins.txt" << std::endl;
	}
	if (coinsFile >> coinsf) {
		std::cout << "Coins: " << coinsf << std::endl;
	}
	else {
		std::cerr << "Failed to read the number from the file." << std::endl;
	}
	coinsFile.close(); // Close the file


	std::ifstream timeFile("results/time.txt"); // Open the file for reading
	if (!timeFile.is_open()) {
		std::cerr << "Failed to open time.txt" << std::endl;
	}
	if (timeFile >> timef) {
		std::cout << "Time: " << timef << std::endl;
	}
	else {
		std::cerr << "Failed to read the number from the file." << std::endl;
	}
	timeFile.close(); // Close the file


	std::ifstream scoreFile("results/score.txt"); // Open the file for reading
	if (!scoreFile.is_open()) {
		std::cerr << "Failed to open score.txt" << std::endl;
	}
	if (scoreFile >> scoref) {
		std::cout << "Score: " << scoref << std::endl;
	}
	else {
		std::cerr << "Failed to read the number from the file." << std::endl;
	}
	scoreFile.close(); // Close the file



    std::ofstream myfile;
    myfile.open("results/Results.txt", std::ios::app);
    
    if (myfile.is_open()) { // Check if the file was opened successfully
        myfile << localData << "Coins: " << properFormat3(coinsf) << " Score: " << properFormat4(scoref) << " Time: " << properFormat3(timef) << " " << userName << std::endl << std::endl;
        myfile.close();
    } else {
        std::cerr << "Error opening the file." << std::endl;
    }
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
	std::cout << "Enter your name : " << std::endl;

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
	system("CLS");
}
