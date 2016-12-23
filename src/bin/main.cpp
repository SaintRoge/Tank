#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <sstream>

#include "../lib/functions.hpp"
#include "../lib/tank.hpp"

using namespace sf;

int main(int argc, char const *argv[]) {

    int windowSizeX(1200), windowSizeY(800);

    RenderWindow window(VideoMode(windowSizeX, windowSizeY), "Tank", Style::Close);

    sf::Music music;
    sf::Sprite overSprite;

    sf::Text text;
    sf::Text outOfAmmoText;
    sf::Font font;

    if (!music.openFromFile("snd/Red.wav")) {
        std::cout << "Sorry, the music can't be loaded" << std::endl;
    } else {
        std::cout << "The music has been loaded" << std::endl;
        music.play();
    }

    if (!font.loadFromFile("font/joystix.ttf")) {
        std::cout << "Fonts can't be loaded" << std::endl;
    } else {
        std::cout << "Fonts have been loaded" << std::endl;
        text.setFont(font);
        outOfAmmoText.setFont(font);
    }

    text.setCharacterSize(60);
    text.setPosition(1060.f, 710.f);

    outOfAmmoText.setString("Out of Ammo !");
    outOfAmmoText.setColor(sf::Color::Red);
    outOfAmmoText.setCharacterSize(100);
    outOfAmmoText.setPosition(90.f, 350.f);

    Tank *tank(NULL);
    tank = new Tank(10); //Creates a new Tank with 10 ammo
    window.draw(*tank);
    tank->setPosition(900, 400);
    tank->setWindowResolution(windowSizeX, windowSizeY);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
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

        if (tank->isOverEnabled()) {
            overSprite = tank->getOverSprite();
        }

        text.setString(std::to_string(tank->getAmmo()));

        window.clear(Color(62, 96, 0));

        if (tank->isOverEnabled()) {
            window.draw(overSprite);
        }

        window.draw(*tank);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) { // Space bar pressed
            if (tank->ifFire()) {
                std::cout << "Fire !" << std::endl;
            } else if (tank->getAmmo() == 0) { // Shoot
                window.draw(outOfAmmoText);
            } 
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            if (tank->ifRecharge()) {
                std::cout << "Reload !" << std::endl;
            } else if (tank->getAmmo() == 0) {
                window.draw(outOfAmmoText);
            }
        }

        window.draw(text);
        window.display();
    }

    delete tank;
    tank = NULL;

    return 0;
}

