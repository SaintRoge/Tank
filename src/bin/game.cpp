#include "../lib/game.hpp"

Game::Game() {
	int windowSizeX(1200), windowSizeY(800);
    int enemiesNumber(6);
    int enemiesScore(0);

    sf::RenderWindow window(sf::VideoMode(windowSizeX, windowSizeY), "Tank", sf::Style::Close);

    sf::Music music;
    sf::Sprite overSprite;

    srand (time(NULL));

    sf::Text text;
    sf::Text outOfAmmoText;
    sf::Font font;

    sf::Texture textureArray[enemiesNumber];
    Enemies enemiesArray[enemiesNumber];

    for (int i(0); i < enemiesNumber; i++) {
        textureArray[i] = randomTexture();
        enemiesArray[i] = Enemies();
        enemiesArray[i].setTexture(textureArray[i]);
        enemiesArray[i].setPosition(-(std::rand() % (windowSizeX -  windowSizeX/2 + 1)), std::rand() % (windowSizeY - 99));
    }

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
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {

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

        window.clear(sf::Color(62, 96, 0));

        if (tank->isOverEnabled()) {
            window.draw(overSprite);
        }

        window.draw(*tank);
        window.draw(text);

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

	for (int j(0); j < enemiesNumber; j++) {
        if (!enemiesArray[j].isDead()) {
        	    window.draw(enemiesArray[j]);
        	    enemiesArray[j].move();
    	} else {
    	    enemiesScore += enemiesArray[j].getScore();
    	    Enemies enemie;
    	    enemie.setTexture(textureArray[rand() % enemiesNumber]);
    	    enemie.setPosition(-(std::rand() % (windowSizeX + windowSizeX/2 + 1)), std::rand() % (windowSizeY - 99));
	        enemiesArray[j] = enemie;
	  }
        }
        
        if (tank->ifBullet()) {
            window.draw(tank->getBullet());
            tank->BulletMove();
        }

        window.draw(text);

        window.display();
    }

    delete tank;
    tank = NULL;
}

Game::~Game() {

}
