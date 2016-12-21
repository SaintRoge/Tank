#include <SFML/Graphics.hpp>

#include "functions.hpp"

using namespace sf;

int main(int argc, char const *argv[]) {
    sf::RenderWindow window(sf::VideoMode(800, 800), "Tank");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.display();
    }

    return 0;
}