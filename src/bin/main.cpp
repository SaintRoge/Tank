#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "../lib/functions.hpp"
#include "../lib/tank.hpp"

using namespace sf;

int main(int argc, char const *argv[]) {
    RenderWindow window(VideoMode(1200, 800), "Tank", Style::Close);

    sf::Music music;

    if (!music.openFromFile("snd/Red.wav")) {
        std::cout << "Sorry, the music can't be loaded" << std::endl;
    } else {
        std::cout << "The music have been loaded" << std::endl;
    }

    Tank *tank(NULL);
    tank = new Tank(); //Creates a new Tank
    window.draw(*tank);
    tank->setPosition(900, 400);

    music.play();

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

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            // Shoot
            tank->fire();
            std::cout << "Fire !" << std::endl;
        }

        window.clear(Color(74, 102, 36));
        window.draw(*tank);
        window.display();
    }

    delete tank;
    tank = NULL;

    return 0;
}