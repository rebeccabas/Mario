#include "Menu.h"


Menu::Menu()
{
	try {
		if (!font.loadFromFile("assets/PixeloidSans.ttf"))
		{
			throw - 1;
		}
	}
	catch (int)
	{
		std::cout << "Error: Cannot load menu font.";
		exit(1);
	}

	menu[0].setFont(font);
	sf::Color color(255, 87, 51);
	menu[0].setFillColor(color);
	menu[0].setString("START GAME");


	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("RESTART");


	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("SCOREBOARD");
	readResultsFromFile();
	loadReslutsToArray();


	menu[3].setFont(font);
	menu[3].setFillColor(sf::Color::White);
	menu[3].setString("EXIT");

	selectedItemIndex = 0;
}

void Menu::followMario(int center)
{
	menu[0].setPosition(sf::Vector2f(center - 95, WINDOW_HEIGHT / (MAX_NUMBER_OF_ITEMS + 1) * 1.25 + 130));
	menu[1].setPosition(sf::Vector2f(center - 55, WINDOW_HEIGHT / (MAX_NUMBER_OF_ITEMS + 1) * 1.6 + 130));
	menu[2].setPosition(sf::Vector2f(center - 95, WINDOW_HEIGHT / (MAX_NUMBER_OF_ITEMS + 1) * 2 + 130));
	menu[3].setPosition(sf::Vector2f(center - 30, WINDOW_HEIGHT / (MAX_NUMBER_OF_ITEMS + 1) * 2.4 + 130));

	resultsToDisplay[0].setPosition(sf::Vector2f(center - 343, 45));
	resultsToDisplay[1].setPosition(sf::Vector2f(center - 342, 70));
	resultsToDisplay[2].setPosition(sf::Vector2f(center - 341, 95));
}



void Menu::drawMenuBackground(sf::RenderWindow& window, int center)
{
	sf::Texture backgroundTexture;
	try {
		if (!backgroundTexture.loadFromFile("assets/titlescreen-2.png"))
		{
			throw - 1;
		}
	}
	catch (int)
	{
		std::cout << "Error: Cannot load menu background texture.";
		exit(1);
	}
	//display background
	sf::Sprite spriteBackground;
	spriteBackground.setTexture(backgroundTexture);
	spriteBackground.setPosition(window.getSize().x /2 - WINDOW_WIDTH / 2, 0);
	
	window.setView(window.getDefaultView());
	window.draw(spriteBackground);
}
void Menu::draw(sf::RenderWindow& window, int center)
{	
	drawMenuBackground(window, center);

	sf::Texture texture;
	try {
		if (!texture.loadFromFile("assets/menuBack-2.png"))
		{
			throw - 1;
		}
	}
	catch (int)
	{
		std::cout << "Error: Cannot load menu background texture.";
		exit(1);
	}
	//display background
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setOrigin({ 190,20 });
	sprite.setPosition({ (float)center,WINDOW_HEIGHT / 2 });
	sf::View view(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
	window.setView(view);
	window.draw(sprite);
	//display option to choose
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}

void Menu::drawBestResults(sf::RenderWindow& window, int center)
{
	drawBestResultsBackground(window, center);
	drawResults(window, center);
}

void Menu::drawResults(sf::RenderWindow& window, int center)
{
	for (int i = 0; i < NUMBER_OF_RESULTS; i++)
	{
		window.draw(resultsToDisplay[i]);
	}
}

void Menu::drawBestResultsBackground(sf::RenderWindow& window, int center) {
	sf::Texture texture;
	try {
		if (!texture.loadFromFile("assets/bestResultsWindow.png"))
		{
			throw - 1;
		}
	}
	catch (int)
	{
		std::cout << "can not load results background texture";
		exit(1);
	}

	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setOrigin(747 / 2, 103 / 2);
	sprite.setPosition({ (float)center,WINDOW_HEIGHT / 6 });
	window.draw(sprite);
}

void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		sf::Color color(255, 87, 51);
		menu[selectedItemIndex].setFillColor(color);
	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		sf::Color color(255, 87, 51);
		menu[selectedItemIndex].setFillColor(color);
	}
}

int Menu::GetPressedItem()
{
	return selectedItemIndex;
}

void Menu::setPressedItem(int item)
{
	selectedItemIndex = item;
}

bool Menu::isON()
{
	return isOn;
}

void Menu::setIsON(bool status)
{
	isOn = status;
	selectedItemIndex = 0;
}

void Menu::readResultsFromFile()
{
	std::string line, line2;
	std::string coinsTemp;;
	std::string scoreTemp;
	std::string timeTemp;
	std::ifstream infile;
	std::string userName;

	loadedResults.clear();

	infile.open("results/results.txt");

	try
	{
		if (!infile)
		{
			throw - 1;
		}
	}
	catch (int)
	{
		std::cout << "can not load results";
		exit(1);
	}

	int counter = 0;

	while (getline(infile, line)) {


		getline(infile, line2);


		coinsTemp = (std::to_string(line2[7] - 48) + std::to_string(line2[8] - 48) + std::to_string(line2[9] - 48));
		scoreTemp = (std::to_string(line2[18] - 48) + std::to_string(line2[19] - 48) + std::to_string(line2[20] - 48) + std::to_string(line2[21] - 48));
		timeTemp = (std::to_string(line2[29] - 48) + std::to_string(line2[30] - 48) + std::to_string(line2[31] - 48));

		userName.clear();
		for (int i = 33; i < line2.length(); i++)
		{
			userName = userName + line2[i];
		}

		loadedResults.push_back(result(line, scoreTemp, timeTemp, coinsTemp, userName));

		coinsTemp.clear();
		scoreTemp.clear();
		timeTemp.clear();

		counter++;
		getline(infile, line2);
	}

	infile.close();

	sortResults();
}

void Menu::loadReslutsToArray()
{
	readResultsFromFile();
	int numberOFResults = NUMBER_OF_RESULTS;
	if (loadedResults.size() < NUMBER_OF_RESULTS)
		numberOFResults = loadedResults.size();

	for (int i = 0; i < numberOFResults; i++)
	{
		std::string toDisplay = std::to_string(i + 1) + ". Score: " + loadedResults.at(i).score + " coins: " + loadedResults.at(i).coins + " time " + loadedResults.at(i).time + "   " + loadedResults.at(i).date + " " + loadedResults.at(i).userName;
		resultsToDisplay[i].setString(toDisplay);

		resultsToDisplay[i].setFont(font);
		resultsToDisplay[i].setFillColor(sf::Color::Black);
		resultsToDisplay[i].setCharacterSize(20);
	}
}

bool Menu::comparator(result  i1, result  i2)
{
	return (i1.score > i2.score);
}
void Menu::sortResults()
{
	std::sort(loadedResults.begin(), loadedResults.end(), comparator);

}

void Menu::gameWon(int center, sf::RenderWindow& window)
{
	sf::Texture texture;
	try {
		if (!texture.loadFromFile("assets/gameWon.png"))
		{
			throw - 1;
		}
	}
	catch (int)
	{
		std::cout << "can not load winning background texture";
		exit(1);
	}
	//display background
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setOrigin({ 190,101 });
	sprite.setPosition({ (float)center, 450 });
	window.draw(sprite);
}
void Menu::reset() {
	selectedItemIndex = 0;
	sf::Color color(255, 87, 51);
	menu[selectedItemIndex].setFillColor(color);
	menu[selectedItemIndex + 1].setFillColor(sf::Color::White);
}

Menu::~Menu()
{
}