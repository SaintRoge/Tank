#include <SFML/Graphics.hpp>
#include <iostream>

#include "../lib/functions.hpp"
#include "../lib/tank.hpp"

using namespace sf;

int main(int argc, char const *argv[]) {
    RenderWindow window(VideoMode(800, 800), "Tank", Style::Close);
    Tank *tank(NULL);
    tank = new Tank(); //Creates a new Tank
    window.draw(*tank);
    tank->setPosition(700, 400);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) {

                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            // while the left arrow is pressed the tank is moving
            tank->move(true);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            // while the left arrow is pressed the tank is moving
            tank->move(false);
        }

        window.clear(Color(74, 102, 36));
        window.draw(*tank);
        window.display();
    }

    delete tank;
    tank = NULL;

    return 0;
}