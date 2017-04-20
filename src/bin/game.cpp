#include "../lib/game.hpp"

Game::Game(sf::RenderWindow *window) {
	m_window = window;

    srand(time(NULL));
    std::cout << "Srand generated at: " << time(NULL) << std::endl;

    m_fullScreenClock.restart();

    std::ifstream file("speedCoef.txt");

    if (file) {
        std::string speedCoef;
        std::getline(file, speedCoef);
        m_speedCoef = std::stof(speedCoef);
        std::cout << "speedCoef file oppened" << std::endl;
    } else {
        std::cout << "Oh shit, you can't open the file !" << std::endl;
    }

	m_windowSize = m_window->getSize();
    m_enemiesNumber = 6;
    m_enemiesScore = 0;
    m_viewSpeed = 25.f * m_speedCoef;
    m_score = 0;
    m_maximumEnemiesScore = 3;

    m_gameover = false;
    m_fullScreen = false;

    std::cout << "parameters are now updated" << std::endl;

    m_aliveHeart.loadFromFile("img/life2.png", sf::IntRect(0, 0, 52, 45));
    m_deadHeart.loadFromFile("img/life1.png", sf::IntRect(0, 0, 52, 45));

    for (int i(0); i < m_enemiesNumber; i++) {
        randomEnemie(i);
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
        m_normalViewText.setFont(m_font);
    }

    m_scoreText.setCharacterSize(30);
    m_scoreText.setPosition(40.f, m_window->getSize().y - 60.f);
    m_scoreText.setString((m_score >= 10) ? "Tonton Adolf : " + std::to_string(m_score) : (m_score > 0) ? "Facho : " + std::to_string(m_score) : (m_score == 0) ? "Gros con sans avis : " + std::to_string(m_score) : (m_score <= -10) ? "Coco : " + std::to_string(m_score) : "Gaucho : " + std::to_string(m_score));
    m_text.setCharacterSize(60);
    m_text.setPosition(m_window->getSize().x - 140.f, m_window->getSize().y - 90.f);

    m_normalViewText.setString("Press 'O' to return to the normal view");
    m_normalViewText.setCharacterSize(25);
    m_normalViewText.setPosition(40.f, 20.f);

    m_secondsText.setString("0s");
    m_secondsText.setCharacterSize(25);
    m_secondsText.setPosition(40.f, 20.f);

    m_outOfAmmoText.setString("Out of Ammo !");
    m_outOfAmmoText.setColor(sf::Color::Red);
    m_outOfAmmoText.setCharacterSize(100);
    m_outOfAmmoText.setPosition(90.f, 350.f);

    m_tank = new Tank(10); //Creates a new Tank with 10 ammo
    m_tank->setPosition(0, 400);
    m_tank->setWindowResolution(m_window->getSize().x, m_window->getSize().y);

    m_fireTime = m_tank->getFireTime();
    m_reloadTime = m_tank->getReloadTime();

    m_life1.setPosition(m_window->getSize().x - 250.f, 10.f);
    m_life2.setPosition(m_window->getSize().x - 185.f, 10.f);
    m_life3.setPosition(m_window->getSize().x - 120.f, 10.f);

}

Game::~Game() {

}

void Game::start() {
    m_gameClock.restart();
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
                resize();
            }
        }

        if (m_enemiesScore >= m_maximumEnemiesScore && !m_gameover) {
            gameover();
            std::cout << "Haaa you looser !" << std::endl;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && !m_gameover) { 
            m_killer = "yourself";
            gameover();
            std::cout << "Haaa you looser !" << std::endl;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F11) && m_fullScreenClock.getElapsedTime() >= sf::seconds(2.f)) {
            if (m_fullScreen) {
                m_fullScreenClock.restart();
                m_window->create(sf::VideoMode(1200, 800), "Tank", sf::Style::Close | sf::Style::Resize);
                m_window->setMouseCursorVisible(false);
                m_fullScreen = false;
            } else { 
                m_fullScreenClock.restart();
                m_window->create(sf::VideoMode(1200, 800), "Tank", sf::Style::Close | sf::Style::Resize | sf::Style::Fullscreen);
                m_window->setMouseCursorVisible(false);
                m_fullScreen = true;
            }
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
        } else if (m_enemiesScore >= 3 && !m_gameover) {
            m_life1.setTexture(m_deadHeart); 
            m_life2.setTexture(m_deadHeart); 
            m_life3.setTexture(m_deadHeart); 
            gameover();                                   
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
            m_life1.setPosition(m_life1.getPosition().x - m_viewSpeed, m_life1.getPosition().y);
            m_life2.setPosition(m_life2.getPosition().x - m_viewSpeed, m_life2.getPosition().y);
            m_life3.setPosition(m_life3.getPosition().x - m_viewSpeed, m_life3.getPosition().y); 
            m_normalViewText.setPosition(m_normalViewText.getPosition().x - m_viewSpeed, m_normalViewText.getPosition().y);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_window->getView().getCenter().x + m_viewSpeed <= (float)m_window->getSize().x/2) {
            sf::FloatRect visibleArea(0, 0, m_window->getSize().x, m_window->getSize().y);
            sf::View view = sf::View(visibleArea);
            view.setCenter(m_window->getView().getCenter().x + m_viewSpeed, m_window->getView().getCenter().y);
            m_window->setView(view);
            m_text.setPosition(m_text.getPosition().x + m_viewSpeed, m_text.getPosition().y);
            m_scoreText.setPosition(m_scoreText.getPosition().x + m_viewSpeed, m_scoreText.getPosition().y);
            m_life1.setPosition(m_life1.getPosition().x + m_viewSpeed, m_life1.getPosition().y);
            m_life2.setPosition(m_life2.getPosition().x + m_viewSpeed, m_life2.getPosition().y);
            m_life3.setPosition(m_life3.getPosition().x + m_viewSpeed, m_life3.getPosition().y);        
            m_normalViewText.setPosition(m_normalViewText.getPosition().x + m_viewSpeed, m_normalViewText.getPosition().y);     
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
	        if (!m_enemiesArray[j].isDead()) {
                m_enemiesArray[j].setWindowSize(m_window->getSize());
        	    m_window->draw(m_enemiesArray[j]);
        	    m_enemiesArray[j].move();
                if (
                    m_tank->ifBullet()
                    &&
                    m_enemiesArray[j].getPosition().x + 100.f >= m_tank->getBullet().getPosition().x 
                    && 
                    m_enemiesArray[j].getPosition().x <= m_tank->getBullet().getPosition().x 
                    &&
                    m_tank->getBullet().getPosition().y + m_tank->getBullet().getSize().y >= m_enemiesArray[j].getPosition().y 
                    &&
                    m_tank->getBullet().getPosition().y <= m_enemiesArray[j].getPosition().y + 100.f
                    ) {

                    std::cout << m_enemiesArray[j].getName() << " Killed" << std::endl;

                    m_enemiesArray[j].killEnemies(true);
                    m_deadMusic.play();
                }
	    	} else {
                if (m_enemiesArray[j].isHumanKill()) {
                    m_tank->setAmmo(m_tank->getAmmo() + std::rand() % 2 + 1);
                    m_score -= m_enemiesArray[j].getScore();
                    m_scoreText.setString((m_score >= 10) ? "Hitler : " + std::to_string(m_score) : (m_score > 0) ? "Facho : " + std::to_string(m_score) : (m_score == 0) ? "Gros con sans avis : " + std::to_string(m_score) : (m_score <= -10) ? "Coco : " + std::to_string(m_score) : "Gaucho : " + std::to_string(m_score));
                    m_tank->killBullet();
                } else {
                    m_killer = m_enemiesArray[j].getName();
                    m_enemiesScore++;
                }
                randomEnemie(j);
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

        if (m_window->getView().getCenter().x < m_window->getSize().x/2) {
            m_window->draw(m_normalViewText);
        } else {
            m_secondsText.setString(std::to_string(m_gameClock.getElapsedTime().asSeconds()) + " seconds");
            m_window->draw(m_secondsText);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_tank->getElapsedFireClockTime() >= m_fireTime && m_tank->ifReloaded()) { // Space bar pressed
            if (m_tank->ifFire()) { // Shoots
                std::cout << "Fire !" << std::endl;
            } else if (m_tank->getAmmo() == 0) { 
                m_window->draw(m_outOfAmmoText);
            } 
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && m_tank->getElapsedReloadClockTime() >= m_reloadTime && !m_tank->ifReloaded()) {
            if (m_tank->ifRecharge()) {
                std::cout << "Reload !" << std::endl;
            } else if (m_tank->getAmmo() == 0) {
                m_window->draw(m_outOfAmmoText); 
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::O) && m_gameover) {
            m_window->setView(sf::View(sf::FloatRect(0, 0, m_window->getSize().x, m_window->getSize().y)));
            resize();
            break;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
            m_window->setView(sf::View(sf::FloatRect(0, 0, m_window->getSize().x, m_window->getSize().y)));
            resize();            
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
    m_gameoverText.setPosition(30, m_window->getSize().y/2 - 200.f);
    m_gameoverText.setString("Haaa you loser\nyou were killed by " + m_killer + "!\nyou survived " + std::to_string(m_gameClock.getElapsedTime().asSeconds()) + " seconds.\nPress 'O' to continue...");
    m_gameoverText.setFont(m_font);
    m_gameover = true;
}

void Game::resize() {
    m_visibleArea = sf::FloatRect(0, 0, m_window->getSize().x, m_window->getSize().y);
    m_window->setView(sf::View(m_visibleArea));
    m_tank->setWindowResolution(m_window->getSize().x, m_window->getSize().y);
    m_text.setPosition(m_window->getSize().x - 140.f, m_window->getSize().y - 90.f);
    m_scoreText.setPosition(40.f, m_window->getSize().y - 60.f);
    m_life1.setPosition(m_window->getSize().x - 250.f, 10.f);
    m_life2.setPosition(m_window->getSize().x - 185.f, 10.f);
    m_life3.setPosition(m_window->getSize().x - 120.f, 10.f);    
    m_gameoverText.setPosition(30, m_window->getSize().y/2 - 200.f);
    m_normalViewText.setPosition(40.f, 20.f);
}

void Game::randomEnemie(int id) {
    sf::Texture texture;
    std::string imgArray[] = {"boutin", "Fillon", "macron", "valls", "juppe", "marine", "melenchon", "sarkozy", "cope", "hollande", "filoche", "cazeneuve", "martine", "dupont-aignan", "asselineau", "lassalle", "poutou", "arthaud", "hamon", "cheminade"};
    int scoreArray[] = {7, 5, -5, 1, 2, 8, -7, 5, 3, -4, -8, -4, -6, 6, 7, 0, -8, -9, -3, -2};
    int enemieNumber(std::rand() % sizeof(imgArray)/sizeof(*imgArray));
    m_enemiesArray[id] = Enemies();
    m_enemiesArray[id].setName(imgArray[enemieNumber]);
    m_enemiesArray[id].setScore(scoreArray[enemieNumber]);
    m_enemiesArray[id].setPosition(-(std::rand() % (int)m_window->getSize().x + 1), std::rand() % (m_windowSize.y - 100) + 1);
    m_enemiesArray[id].setSpeed((float)(std::rand() % 1500 + 100) / 100.f);
    texture.loadFromFile("img/" + m_enemiesArray[id].getName() + ".png", sf::IntRect(0, 0, 100, 100));
    m_textureArray[id] = texture;
    m_enemiesArray[id].setTexture(m_textureArray[id]);
    std::cout << enemieNumber << ": " << imgArray[enemieNumber] <<  " with the speed of " << m_enemiesArray[id].getSpeed() << " and score of " << m_enemiesArray[id].getScore() << " was generated in x: " << m_enemiesArray[id].getPosition().x << " y: " << m_enemiesArray[id].getPosition().y << std::endl;
}
