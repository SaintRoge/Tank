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
    Text quitButton;

    Font font;

    font.loadFromFile("font/joystix.ttf");

    bool playSelect(true);
    bool quitSelect(false);

    Clock choiceClock;
    choiceClock.restart();

    Music buttonMusic;

    buttonMusic.openFromFile("snd/jeanne.wav");

    playButton.setString("  Play");
    playButton.setFont(font);
    playButton.setCharacterSize(60);
    playButton.setPosition(500.f, 250.f);

    quitButton.setString("  Quit");
    quitButton.setFont(font);
    quitButton.setCharacterSize(60);
    quitButton.setPosition(500.f, 500.f);

    Game game(&window);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {

                window.close();
            }
        }

        if (playSelect) {
            playButton.setString("> Play");
            playButton.setColor(Color::Red);
            quitButton.setString("  Quit");
            quitButton.setColor(Color::White);
        } else {
            quitButton.setString("> Quit");
            quitButton.setColor(Color::Red);
            playButton.setString("  Play");
            playButton.setColor(Color::White);
        }

        if ((Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::Down)) && choiceClock.getElapsedTime() >= seconds(0.1)) {
            choiceClock.restart();
            buttonMusic.play();
            playSelect = !playSelect;
            quitSelect = !quitSelect;
        }

        if (Keyboard::isKeyPressed(Keyboard::Return)) {
            if (playSelect) {
                game.start();
            } else {
                window.close();
            }
            break;
        }

        window.clear();
        window.draw(playButton);
        window.draw(quitButton);
        window.display();

    }

    return 0;
}

