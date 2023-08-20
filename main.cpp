#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include <iostream>
#include "Game.h"

int main()
{
    Game game;
    sf::SoundBuffer buffer;
    sf::Sound bgsound;

    if (!buffer.loadFromFile("assets/bgm.wav")) {
        // error handling
        std::cout << "Can't find sound file" << std::endl;
    }
    bgsound.setBuffer(buffer);

    if (bgsound.getStatus() != sf::Sound::Playing) {
        bgsound.setLoop(true);  // Set the sound to loop
        bgsound.play();
    }

    game.run();
    return 0;
}