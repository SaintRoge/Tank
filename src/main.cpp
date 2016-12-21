#include <SFML/Graphics.hpp>
#include <iostream>

#include "functions.hpp"

using namespace sf;

int main(int argc, char const *argv[]) {
    sf::RenderWindow window(sf::VideoMode(800, 800), "Tank");

    const std::string img("../img/Tank-GTAA.png");
    sf::Texture texture;

    if (!texture.loadFromFile(img, sf::IntRect(10, 10, 32, 32))) {
	    std::cout << "Sorry, " << img << " can't be load" << std::endl;
	}

	if (!texture.create(200, 200)) {
	    std::cout << "Sorry, the texture can't be created" << std::endl;
	}

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(74, 102, 36));
        window.display();
    }

    return 0;
}