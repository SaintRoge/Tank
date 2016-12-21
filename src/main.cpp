#include <SFML/Graphics.hpp>
#include <iostream>

#include "functions.hpp"

using namespace sf;

int main(int argc, char const *argv[]) {
    sf::RenderWindow window(sf::VideoMode(800, 800), "Tank", sf::Style::Close | sf::Style::Resize);

    window.clear(sf::Color(74, 102, 36));

    const std::string img("img/Tank-GTAA.png");
    sf::Texture texture;

    if (!texture.loadFromFile(img, sf::IntRect(0, 0, 32, 32))) {
	    std::cout << "Sorry, " << img << " can't be load" << std::endl;
	}

	if (!texture.create(145, 229)) {
	    std::cout << "Sorry, the texture can't be created" << std::endl;
	}

	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setOrigin(sf::Vector2f(-500, -300));
	sprite.rotate(15);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //window.clear(sf::Color(74, 102, 36));
        window.display();
        window.draw(sprite);
    }

    return 0;
}