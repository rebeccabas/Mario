#include "Game.h"

Game::Game()
{
	// window initialization
	this->window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mario");

	map.load("assets/map.png", sf::Vector2u(64, 64));

	view.reset(sf::FloatRect(0.f, 0.f, WINDOW_WIDTH, WINDOW_HEIGHT));

	gameInfo.reset();

	addMobs();

	mushroomBuffer.loadFromFile(MUSHROOM_SOUND);
	mushroomSound.setBuffer(mushroomBuffer);

}

Game::~Game()
{
	delete this->window;
}

void Game::intersection(Mario& mario, Entity& entity)
{
	Bonus b;
	if (entity.getIsAlive()) {
		if (mario.getSprite().getGlobalBounds().intersects(entity.getSprite().getGlobalBounds()))
			if (entity.getIsFriendly())	// if entity is friendly mario collect it
			{
				entity.dead();
				mario.setBigMario(true);
				mushroomSound.play();
				gameInfo.increaseScoreBonus();
			}
			else
			{
				if (abs(mario.bottom() - entity.top()) < 10 && abs(mario.left() - entity.left()) < 54 && entity.isKillable())	// mario jumped on the entity
				{
					if (mario.getIsAlive())
					{
						mario.killingMove();
						entity.dead();
						gameInfo.increaseScoreBonus();
					}
				}
				else // mario was hit by the entity 
				{
					if (entity.getIsAlive())
					{
						menu.setIsON(true);
						mario.killingMove();
						mario.killingMove();
						mario.dead();
						int g = gameInfo.getLife();
						if (g <= 0)
						{
							gameInfo.resetLife();
						}
						gameInfo.showLife();
						if (mario.getIsAlive()) {
							menu.setIsON(false);
							view.setCenter(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
						}
					}
				}
			}
	}
}

void Game::updateSFMLEvents()
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
			this->window->close();
		if (this->sfEvent.type == sf::Event::KeyReleased)
		{
			if (sfEvent.key.code == Keyboard::Escape)
			{
				menu.setIsON(true);
			}
			// screen shots
			if (sfEvent.key.code == Keyboard::F1)
			{
				screenshot.create(window);
			}
		}
	}
}

void Game::update()
{
	this->updateSFMLEvents();

	for (int i = 0; i < mobs.size(); i++)
	{
		if (abs((mario.getPosition().x - mobs.at(i).getPosition().x)) < WINDOW_WIDTH / 1.6) // OPTIMALIZATION (only mobs in WINDOW_WIDTH / 1.6 distance are moved)
		{
			intersection(mario, mobs.at(i));

			if (mobs.at(i).getIsAlive())
			{
				int movingSide = map.collison(mobs.at(i), gameInfo);

				if (movingSide == LEFT)
					mobs.at(i).MovingDirectiongLeft();
				else if (movingSide == RIGHT)
					mobs.at(i).MovingDirectiongRight();

				mobs.at(i).update();
			}
		}
	}//

	int marioHit = map.collison(mario, gameInfo);
	map.collison(mario, gameInfo);
	if (marioHit == BOTTOM)	// if mario on the ground he can jump
	{
		mario.setCanJump(true);
	}
	if (marioHit == TOP)
	{
		mario.fallDown();
		mario.setCanJump(false);
	}
	if (!mario.getIsAlive())
		menu.setIsON(true);

	if (marioHit == END_GAME && !won)
	{
		window->setVisible(false);
		menu.isON();
		gameInfo.saveResultToFile();
		window->setVisible(true);
		mario.dead();	// die twice, cause mario may have additional life
		mario.dead();
		won = true;
	}

	mario.update(map.getMapWidth());

	Bonuses();	// update bonuses
}

void Game::render()
{
	this->window->clear();

	window->draw(map);

	// follow mario to display in right place when called
	gameInfo.followMario(view.getCenter().x);
	menu.followMario(mario.getPosition().x);

	gameInfo.draw(*window, view.getCenter().x);

	if (mario.getIsAlive())
		window->draw(mario);

	drawMobs();

	cameraMovement();

	window->setView(view);
	this->window->display();
}

void Game::Menu(int center)
{
	if (center < WINDOW_WIDTH / 2)
		center = WINDOW_WIDTH / 2;

	menu.followMario(center);
	menu.draw(*window, center);

	if (won)
	{
		menu.gameWon(center, *window);
		menu.isON();
	}

	if (menu.GetPressedItem() == 2)
	{
		menu.drawBestResults(*window, center);
	}
	this->window->display();
	while (window->pollEvent(sfEvent))
	{
		if (sfEvent.type == Event::Closed)
			window->close();

		if (sfEvent.type == Event::KeyReleased)
		{
			if (sfEvent.key.code == Keyboard::Up)
			{
				menu.MoveUp();
			}
			if (sfEvent.key.code == Keyboard::Down)
			{
				menu.MoveDown();
			}
			if (sfEvent.key.code == Keyboard::Enter)
			{
				if (menu.GetPressedItem() == 0)
				{
					if (mario.getIsAlive() == false)
					{
						menu.setPressedItem(1);
						menu.loadReslutsToArray();
					}
					else
						menu.setIsON(false);
				}
				if (menu.GetPressedItem() == 1)
				{
					mario.reset();
					menu.reset();
					won = false;
					mario.setBigMario(false);
					addMobs();


					view.reset(sf::FloatRect(0.f, 0.f, WINDOW_WIDTH, WINDOW_HEIGHT));
					gameInfo.reset();
					map.loadArrayFromArray("assets/array.txt");
					map.load("assets/map.png", sf::Vector2u(64, 64));
					menu.setIsON(false);
				}
				if (menu.GetPressedItem() == 3)
				{
					window->close();
					delete this->window;
					exit(0);
				}
			}
		}
	}
}

void Game::run()
{
	while (this->window->isOpen())
	{
		if (menu.isON())
			Menu(view.getCenter().x);
		else {
			this->update();
			this->render();
			gameInfo.countTime();
		}
	}
}

void Game::cameraMovement()
{
	if (mario.getPosition().x > WINDOW_WIDTH / 2)
		view.setCenter({ mario.getPosition().x, WINDOW_HEIGHT / 2 });
}

void Game::repairSFMLTextures()
{
	//SFML
	//SFML error:
	//Object has its texture after adding it to some container, texture gets lost and replaced with white texture.
	//To solve this repairSFMLTexture() function was added to reload textures when our object are yet in container.
	for (int i = 0; i < mobs.size(); i++)
	{
		mobs.at(i).repair();
	}
}

void Game::drawMobs()
{
	for (int i = 0; i < mobs.size(); i++)
	{
		if (mobs[i].getIsAlive())
			window->draw(mobs.at(i));
	}
}

void Game::Bonuses()
{
	if (map.getBonus() == true)
	{
		Bonus bonus({ mario.getPosition().x - 100, mario.getPosition().y - 128 });
		mobs.push_back(bonus);

		repairSFMLTextures();
		map.setBonus(false);
	}
}

void Game::addMobs()
{
	// Mobs are read from file and add to the vector
	// file structure
	// mobName Posiion.x,Position.y
	// example
	// Turtle 0200,130
	// Spikey 3600,400

	std::string line;
	float x, y;
	std::fstream infile;
	std::string mobName;
	Entity* wsk;

	mobs.clear();

	infile.open("assets/mobs.txt");
	if (!infile) {
		std::cout << "can not open file to read results from";
	}

	while (getline(infile, line)) {
		{
			mobName = line.substr(0, 6);

			x = atof(line.substr(7, 4).c_str());
			y = atof(line.substr(12, 3).c_str());

			if (mobName.compare("Turtle") == 0)
				wsk = new Turtle;

			else if (mobName.compare("Spikey") == 0)
				wsk = new Spikey;
			else
				wsk = new FlyTur; // if no mobName read from exist take FlyTur  

			wsk->setPosition({ x, y });
			mobs.push_back(*wsk);
		}
	}

	infile.close();

	repairSFMLTextures();
}

