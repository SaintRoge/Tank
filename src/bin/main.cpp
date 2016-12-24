#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h> 

#include "../lib/functions.hpp"
#include "../lib/tank.hpp"
#include "../lib/bullet.hpp"
#include "../lib/enemies.hpp"
#include "../lib/game.hpp"

using namespace sf;

int main(int argc, char const *argv[]) {

    RenderWindow window(VideoMode(1200, 800), "Tank", sf::Style::Close);

    Text playButton;
    Font font;

    font.loadFromFile("font/joystix.ttf");

    playButton.setString("Play");
    playButton.setFont(font);
    playButton.setCharacterSize(60);
    playButton.setPosition(500.f, 300.f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {

                window.close();
            }
        }

        window.clear();
        window.draw(playButton);
        window.display();

    }

    /*Game game(&window);
    game.start();*/

    return 0;
}

