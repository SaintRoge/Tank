#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h> 
#include <fstream>

#include "../lib/functions.hpp"
#include "../lib/tank.hpp"
#include "../lib/bullet.hpp"
#include "../lib/enemies.hpp"
#include "../lib/game.hpp"

using namespace sf;

int main(int argc, char const *argv[]) {

    RenderWindow window(VideoMode(1200, 800), "Tank", Style::Close | Style::Resize);

    window.setMouseCursorVisible(false);
    
    Text playButton;
    Text quitButton;

    Font font;

    font.loadFromFile("font/joystix.ttf");

    bool playSelect(true);
    bool quitSelect(false);
    bool fullScreen(false);

    Clock choiceClock;
    Clock fullScreenClock;
    choiceClock.restart();
    fullScreenClock.restart();

    Music buttonMusic;

    buttonMusic.openFromFile("snd/jeanne.wav");

    playButton.setString("  Play");
    playButton.setFont(font);
    playButton.setCharacterSize(60);
    playButton.setPosition(430.f, 250.f);

    quitButton.setString("  Quit");
    quitButton.setFont(font);
    quitButton.setCharacterSize(60);
    quitButton.setPosition(430.f, 400.f);

    Game *game = new Game(&window);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {

                window.close();
            }
            if (event.type == Event::Resized) {
                FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(View(visibleArea));
                game->resize();
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::F11) && fullScreenClock.getElapsedTime() >= seconds(2.f)) {
            if (fullScreen) {
                fullScreenClock.restart();
                window.create(VideoMode(1200, 800), "Tank", Style::Close | Style::Resize);
                game->resize();
                fullScreen = false;       
            } else {
                fullScreenClock.restart();
                window.create(VideoMode(1200, 800), "Tank", Style::Close | Style::Resize | Style::Fullscreen);
                game->resize();
                fullScreen = true;                
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
                game = new Game(&window);
                std::cout << "Start !" << std::endl;
                game->start();
                window.setView(View(FloatRect(0, 0, window.getSize().x, window.getSize().y)));
            } else {
                window.close();
            }
        }

        window.clear();
        window.draw(playButton);
        window.draw(quitButton);
        window.display();

    }

    return 0;
}

