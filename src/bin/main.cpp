#include <SFML/Graphics.hpp>
#include <iostream>

#include "../lib/functions.hpp"
#include "../lib/tank.hpp"

using namespace sf;

int main(int argc, char const *argv[]) {
    sf::RenderWindow window(sf::VideoMode(800, 800), "Tank", sf::Style::Close);
    Tank *tank = new Tank();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                delete tank;

                tank = NULL;

                window.close();
            }
        }

        window.clear(sf::Color(74, 102, 36));
        window.display();
        window.draw(*tank);
    }


    return 0;
}