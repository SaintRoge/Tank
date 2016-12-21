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
    tank->setPosition(400, 400);
    sf::Vector2f v1(2.f, 0.f);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) {

                window.close();
            }
        }

        window.clear(Color(74, 102, 36));
        window.draw(*tank);
        tank->setPosition(tank->getPosition() - v1);
        window.display();
    }

    delete tank;
    tank = NULL;

    return 0;
}