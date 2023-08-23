#include "Game.h"
#include "GameInfo.h"

Game::Game()
{
	// window initialization
	
	this->window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mario");

	map.load("assets/image/map-01.png", sf::Vector2u(64, 64)); //contains objects for map

	view.reset(sf::FloatRect(0.f, 0.f, WINDOW_WIDTH, WINDOW_HEIGHT));

	gameInfo.reset(); //resets game stats

	addMobs(); //adds enemies

	//when mario eats mushroom
	mushroomBuffer.loadFromFile(MUSHROOM_SOUND);
	mushroomSound.setBuffer(mushroomBuffer);
}

Game::~Game()
{
	delete this->window;
}

void Game::intersection(Mario& mario, Entity& entity) //handle collision of mario and mobs
{
	Bonus b;
	if (entity.getIsAlive()) {
		if (mario.getSprite().getGlobalBounds().intersects(entity.getSprite().getGlobalBounds()))
			if (entity.getIsFriendly())	//if entity is friendly mario collects it
			{
				entity.dead();
				mario.setBigMario(true); 
				mushroomSound.play();
				gameInfo.increaseScoreBonus();
			}
			else //if entity is not friendly
			{
				if (abs(mario.bottom() - entity.top()) < 10 && abs(mario.left() - entity.left()) < 54 && entity.isKillable())	//mario jumped on the entity, entity dies
				{
					if (mario.getIsAlive())
					{
						mario.killingMove();
						entity.dead();
						stompBuffer.loadFromFile(STOMP_SOUND);
						stompSound.setBuffer(stompBuffer);
						stompSound.play();
						gameInfo.increaseScoreBonus();
					}
				}
				else //mario was hit by the entity, mario dies
				{
					if (entity.getIsAlive())
					{
						menu.setIsON(true); //if all lives lost, shows menu
						mario.killingMove();
						mario.killingMove();
						mario.dead();

						if (mario.lives == 2)
						{
							gameInfo.showLife2();
						}
						else if (mario.lives == 1)
						{
							gameInfo.showLife1();
						}
						
						if (mario.getIsAlive()) {
							menu.setIsON(false); //if mario still has lives, doesn't show menu
							view.setCenter(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2); //center view on mario
						}
					}
				}
			}
	}
}

void Game::updateSFMLEvents() //handles pause and exit
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed) //when player closes window
			this->window->close();
		if (this->sfEvent.type == sf::Event::KeyReleased) //when player presses esc, game pauses
		{
			if (sfEvent.key.code == Keyboard::Escape)
			{
				menu.setIsON(true);
			}
		}
	}

}

void Game::update()
{
	this->updateSFMLEvents(); //handles pause and exit

	for (int i = 0; i < mobs.size(); i++)
	{
		if (abs((mario.getPosition().x - mobs.at(i).getPosition().x)) < WINDOW_WIDTH / 1.6) //for optimization, mobs are created only when mario is near
		{
			intersection(mario, mobs.at(i)); //checks if mario has touched mob

			if (mobs.at(i).getIsAlive()) //handles movement of mobs; if mob hits brick direction reversed
			{
				int movingSide = map.collision(mobs.at(i), gameInfo); 

				if (movingSide == LEFT)
					mobs.at(i).MovingDirectiongLeft();
				else if (movingSide == RIGHT)
					mobs.at(i).MovingDirectiongRight();

				mobs.at(i).update();
			}
		}

		
	}

	int marioHit = map.collision(mario, gameInfo); //checks what mario is touching
	map.collision(mario, gameInfo);
	if (marioHit == BOTTOM)	//if mario is on the ground he can jump
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

	if (marioHit == END_GAME && !won) //if mario reaches end game point
	{	
		//resets mario's lives, opens window to input name to save score
		//also prompts "You Win" screen
		sf::Time delayTime = sf::milliseconds(200);
		mario.isAlive = false;
		window->clear();
		window->setVisible(false);
		mario.lives = 0;
		mario.goToStart();
		menu.isON();
		gameInfo.saveResultToFile();
		window->setVisible(true);
		sf::sleep(delayTime);
	
		won = true;

	}



	mario.update(map.getMapWidth());

	Bonuses();	//update bonuses
}

void Game::render()
{
	this->window->clear();

	window->draw(map);

	//always prints game stats in center
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

void Game::Menu(int center) //handles controls in menu
{
	if (center != WINDOW_WIDTH / 2)
		center = WINDOW_WIDTH / 2;

	menu.followMario(center); //always draws menu in the center
	menu.draw(*window, center); //draws menu

	if (won) //if game won
	{
		mario.lives = 3;
		menu.gameWon(center, *window);
		menu.isON();
	}

	if (menu.GetPressedItem() == 2) 
	{
		menu.drawBestResults(*window, center);
	}

	if (menu.GetPressedItem() == 3)
	{
		menu.drawHelpMenu(*window, center);
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
						menu.loadResultsToArray();
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
					map.loadArrayFromArray("assets/txt/array.txt");
					map.load("assets/image/map-01.png", sf::Vector2u(64, 64));
					menu.setIsON(false);
				}
				if (menu.GetPressedItem() == 4)
				{
					window->close();
					delete this->window;
					exit(0);
				}
			}
		}
	}
}

void Game::run() //starts game
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

void Game::cameraMovement() //sets view on mario
{
	if (mario.getPosition().x != WINDOW_WIDTH / 2)
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

	infile.open("assets/txt/mobs.txt");
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

			else if (mobName.compare("FlyTur") == 0)
				wsk = new FlyTur;

			else if (mobName.compare("Plant1") == 0)
				wsk = new Plant1;

			else if (mobName.compare("Plant2") == 0)
				wsk = new Plant2;

			else
				wsk = new Abysss; // if no mobName read from exist take Abysss

			wsk->setPosition({ x, y });
			mobs.push_back(*wsk);
		}
	}

	infile.close();

	repairSFMLTextures();
}

