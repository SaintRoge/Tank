#include <SFML/Graphics.hpp>
#include <iostream>

#include "../lib/functions.hpp"
#include "../lib/tank.hpp"

using namespace sf;

int main(int argc, char const *argv[]) {
    RenderWindow window(VideoMode(800, 800), "Tank", Style::Close);
    Tank *tank = new Tank();

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) {
                delete tank;

                tank = NULL;

                window.close();
            }
        }

        window.clear(Color(74, 102, 36));
        window.display();
        window.draw(*tank);
    }


    return 0;
}