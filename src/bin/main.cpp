#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "../lib/functions.hpp"
#include "../lib/tank.hpp"

using namespace sf;

int main(int argc, char const *argv[]) {

    int windowSizeX(1200), windowSizeY(800);

    RenderWindow window(VideoMode(windowSizeX, windowSizeY), "Tank", Style::Close);

    sf::Music music;

    if (!music.openFromFile("snd/Red.wav")) {
        std::cout << "Sorry, the music can't be loaded" << std::endl;
    } else {
        std::cout << "The music has been loaded" << std::endl;
        music.play();
    }

    Tank *tank(NULL);
    tank = new Tank(); //Creates a new Tank
    window.draw(*tank);
    tank->setPosition(900, 400);
    tank->setWindowResolution(windowSizeX, windowSizeY);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) {

                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            tank->move(true);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            tank->move(false);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) { // Space bar pressed
            if (!tank->ifFire()) {
            } else { // Shoot
                std::cout << "Fire !" << std::endl;
            }
        }

        window.clear(Color(74, 102, 36));
        window.draw(*tank);
        window.display();
    }

    delete tank;
    tank = NULL;

    return 0;
}