#include <SFML/Graphics.hpp>
#include <iostream>

#include "../lib/functions.hpp"
#include "../lib/tank.hpp"

using namespace sf;

int main(int argc, char const *argv[]) {
    RenderWindow window(VideoMode(800, 800), "Tank", Style::Close);
    Tank *tank(NULL);
    tank = new Tank();
    window.draw(*tank);

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
        window.display();
    }

    delete tank;
    tank = NULL;

    return 0;
}