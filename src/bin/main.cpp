#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h> 

#include "../lib/functions.hpp"
#include "../lib/tank.hpp"
#include "../lib/bullet.hpp"
#include "../lib/enemies.hpp"
#include "../lib/game.hpp"

using namespace sf;

int main(int argc, char const *argv[]) {

    RenderWindow window(VideoMode(1200, 800), "Tank", sf::Style::Close);
    Game game(&window);
    game.start();

    return 0;
}

