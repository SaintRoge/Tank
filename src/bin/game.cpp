#include "../lib/game.hpp"

Game::Game(sf::RenderWindow *window) {
	m_window = window;

	m_windowSize = m_window->getSize();
    m_enemiesNumber = 4;
    m_enemiesScore = 0;
    m_viewSpeed = 25.f;
    m_score = 0;
    m_maximumEnemiesScore = 3;

    m_ifArraySet = false;
    m_gameover = false;

    srand(time(NULL));

    m_aliveHeart.loadFromFile("img/life2.png", sf::IntRect(0, 0, 52, 45));
    m_deadHeart.loadFromFile("img/life1.png", sf::IntRect(0, 0, 52, 45));

    for (int i(0); i < m_enemiesNumber; i++) {
        m_namesArray.push_back("yourself");
        m_textureArray.push_back(randomTexture(i));
        m_enemiesArray.push_back(Enemies());
        m_enemiesArray[i].setPosition(-(std::rand() % (int)m_window->getSize().x + 1), std::rand() % (m_windowSize.y - 100) + 1);
        m_enemiesArray[i].setTexture(m_textureArray[i]);
    }

    if (!m_music.openFromFile("snd/Red.wav")) {
        std::cout << "Sorry, the music can't be loaded" << std::endl;
    } else {
        std::cout << "The music has been loaded" << std::endl;
    }

    if (!m_deadMusic.openFromFile("snd/dead.wav")) {
        std::cout << "Sorry, the music can't be loaded" << std::endl;
    } else {
        std::cout << "The music has been loaded" << std::endl;
    }

    if (!m_font.loadFromFile("font/joystix.ttf")) {
        std::cout << "Fonts can't be loaded" << std::endl;
    } else {
        std::cout << "Fonts have been loaded" << std::endl;
        m_text.setFont(m_font);
        m_outOfAmmoText.setFont(m_font);
        m_scoreText.setFont(m_font);
    }

    m_scoreText.setCharacterSize(30);
    m_scoreText.setPosition(40.f, m_window->getSize().y - 60.f);
    m_scoreText.setString("Score : " + std::to_string(m_score));
    m_text.setCharacterSize(60);
    m_text.setPosition(m_window->getSize().x - 140.f, m_window->getSize().y - 90.f);

    m_outOfAmmoText.setString("Out of Ammo !");
    m_outOfAmmoText.setColor(sf::Color::Red);
    m_outOfAmmoText.setCharacterSize(100);
    m_outOfAmmoText.setPosition(90.f, 350.f);

    m_tank = new Tank(10); //Creates a new Tank with 10 ammo
    m_tank->setPosition(0, 400);
    m_tank->setWindowResolution(m_window->getSize().x, m_window->getSize().y);

    m_life1.setPosition(m_window->getSize().x - 250.f, 10.f);
    m_life2.setPosition(m_window->getSize().x - 185.f, 10.f);
    m_life3.setPosition(m_window->getSize().x - 120.f, 10.f);
}

Game::~Game() {

}

void Game::start() {
	m_music.play();
    sf::View minimap;
    minimap.setSize(sf::Vector2f(m_windowSize.x, m_windowSize.y));
    minimap.setViewport(sf::FloatRect(0.75f, 0, 0.25f, 0.25f));

    while (m_window->isOpen()) {
        sf::Event event;
        while (m_window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {

                m_window->close();
            }
            if (event.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                m_window->setView(sf::View(visibleArea));
                m_tank->setWindowResolution(m_window->getSize().x, m_window->getSize().y);
                m_text.setPosition(m_window->getSize().x - 140.f, m_window->getSize().y - 90.f);
                m_scoreText.setPosition(40.f, m_window->getSize().y - 60.f);
                m_life1.setPosition(m_window->getSize().x - 250.f, 10.f);
                m_life2.setPosition(m_window->getSize().x - 185.f, 10.f);
                m_life3.setPosition(m_window->getSize().x - 120.f, 10.f);    
                m_gameoverText.setPosition(30, m_window->getSize().y/2 - 100.f);
            }
        }

        if (m_enemiesScore >= m_maximumEnemiesScore && !m_gameover) {
            gameover();
            std::cout << "Haaa you looser !" << std::endl;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && !m_gameover) { // Space bar pressed
            m_killer = "yourself";
            gameover();
            std::cout << "Haaa you looser !" << std::endl;
        }

        if (m_enemiesScore == 0) {
            m_life1.setTexture(m_aliveHeart);
            m_life2.setTexture(m_aliveHeart);
            m_life3.setTexture(m_aliveHeart);
        } else if (m_enemiesScore == 1) {
            m_life1.setTexture(m_aliveHeart);
            m_life2.setTexture(m_aliveHeart);
            m_life3.setTexture(m_deadHeart);
        } else if (m_enemiesScore == 2) {
            m_life1.setTexture(m_aliveHeart);
            m_life2.setTexture(m_deadHeart);
            m_life3.setTexture(m_deadHeart);            
        } else {
            m_life1.setTexture(m_deadHeart); 
            m_life2.setTexture(m_deadHeart); 
            m_life3.setTexture(m_deadHeart);                                     
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            m_tank->move(true);
        }


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            m_tank->move(false);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            sf::FloatRect visibleArea(0, 0, m_window->getSize().x, m_window->getSize().y);
            sf::View view = sf::View(visibleArea);
            view.setCenter(m_window->getView().getCenter().x - m_viewSpeed, m_window->getView().getCenter().y);
            m_window->setView(view);
            m_text.setPosition(m_text.getPosition().x - m_viewSpeed, m_text.getPosition().y);
            m_scoreText.setPosition(m_scoreText.getPosition().x - m_viewSpeed, m_scoreText.getPosition().y);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_window->getView().getCenter().x + m_viewSpeed <= (float)m_window->getSize().x/2) {
            sf::FloatRect visibleArea(0, 0, m_window->getSize().x, m_window->getSize().y);
            sf::View view = sf::View(visibleArea);
            view.setCenter(m_window->getView().getCenter().x + m_viewSpeed, m_window->getView().getCenter().y);
            m_window->setView(view);
            m_text.setPosition(m_text.getPosition().x + m_viewSpeed, m_text.getPosition().y);
            m_scoreText.setPosition(m_scoreText.getPosition().x + m_viewSpeed, m_scoreText.getPosition().y);
        }

        if (m_tank->isOverEnabled()) {
            m_overSprite = m_tank->getOverSprite();
        }

        m_text.setString(std::to_string(m_tank->getAmmo()));

        m_window->clear(sf::Color(62, 96, 0));

        if (m_tank->isOverEnabled()) {
            m_window->draw(m_overSprite);
        }

        m_window->draw(*m_tank);

		for (int j(0); j < m_enemiesNumber; j++) {
	        if (!m_enemiesArray[j].isDead() && m_ifArraySet) {
                m_enemiesArray[j].setWindowSize(m_window->getSize());
        	    m_window->draw(m_enemiesArray[j]);
        	    m_enemiesArray[j].move();
                if (m_tank->ifBullet()) {
                    if (
                        m_enemiesArray[j].getPosition().x + 100.f >= m_tank->getBullet().getPosition().x 
                        && 
                        m_enemiesArray[j].getPosition().x <= m_tank->getBullet().getPosition().x 
                        &&
                        m_tank->getBullet().getPosition().y + m_tank->getBullet().getSize().y >= m_enemiesArray[j].getPosition().y 
                        &&
                        m_tank->getBullet().getPosition().y <= m_enemiesArray[j].getPosition().y + 100.f
                        ) {

                        m_enemiesArray[j].killEnemies();
                        std::cout << j << "Killed" << std::endl;
                        m_score++;
                        m_deadMusic.play();
                        m_tank->setAmmo(m_tank->getAmmo() + std::rand() % 2 + 1);
                        m_scoreText.setString("Score : " + std::to_string(m_score));
                        m_tank->killBullet();
                    }
                }
	    	} else {
                m_killer = m_namesArray[j];
                m_enemiesScore += m_enemiesArray[j].getScore();
                m_enemiesArray[j] = Enemies();
                m_enemiesArray[j].setPosition(-(std::rand() % (int)m_window->getSize().x + 1), std::rand() % (m_windowSize.y - 100) + 1);
                m_textureArray[j] = randomTexture(j);
                m_enemiesArray[j].setTexture(m_textureArray[j]);
                m_ifArraySet = true;
		  	}
        }
        
        if (m_tank->ifBullet()) {
            m_window->draw(m_tank->getBullet());
            m_tank->BulletMove();
        }

        m_window->draw(m_text);
        m_window->draw(m_scoreText);
        m_window->draw(m_life1);
        m_window->draw(m_life2);
        m_window->draw(m_life3);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) { // Space bar pressed
            if (m_tank->ifFire()) {
                std::cout << "Fire !" << std::endl;
            } else if (m_tank->getAmmo() == 0) { // Shoot
                m_window->draw(m_outOfAmmoText);
            } 
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            if (m_tank->ifRecharge()) {
                std::cout << "Reload !" << std::endl;
            } else if (m_tank->getAmmo() == 0) {
                m_window->draw(m_outOfAmmoText); 
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::O) && m_gameover) {
            break;
        }

        if (m_gameover) {
            m_window->clear();
            m_window->draw(m_gameoverText);
            m_window->draw(m_scoreText);
        }

        m_window->display();
    }

    delete m_tank;
    m_tank = NULL;
}

void Game::gameover() {
    m_music.stop();
    m_gameoverText.setCharacterSize(50);
    m_gameoverText.setPosition(30, m_window->getSize().y/2 - 100.f);
    m_gameoverText.setString("Haaa you looser\nyou were killed by " + m_killer + "\n! Press 'O' to continue...");
    m_gameoverText.setFont(m_font);
    m_gameover = true;
}

sf::Texture Game::randomTexture(int id) {
    sf::Texture texture;
    std::string imgArray[] = {"boutin", "Fillon", "macron", "valls", "juppe"};
    m_namesArray[id] = imgArray[std::rand() % (sizeof(imgArray)/sizeof(*imgArray))];
    texture.loadFromFile("img/" + m_namesArray[id] + ".png", sf::IntRect(0, 0, 100, 100));
    return texture;

}