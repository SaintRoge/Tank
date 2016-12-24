#include "../lib/game.hpp"

Game::Game(sf::RenderWindow *window) {
	m_window = window;

	m_windowSize = m_window->getSize();
    m_enemiesNumber = 5;
    m_enemiesScore = 0;
    m_viewSpeed = 25.f;

    srand(time(NULL));

    for (int i(0); i < m_enemiesNumber; i++) {
        m_textureArray.push_back(randomTexture());
        m_enemiesArray.push_back(Enemies());
        m_enemiesArray[i].setTexture(m_textureArray[i]);
        m_enemiesArray[i].setPosition(-(std::rand() % (m_windowSize.x/2) + 1), std::rand() % (m_windowSize.y - 100) + 1);
    }

    if (!m_music.openFromFile("snd/Red.wav")) {
        std::cout << "Sorry, the m_music can't be loaded" << std::endl;
    } else {
        std::cout << "The m_music has been loaded" << std::endl;
    }

    if (!m_font.loadFromFile("font/joystix.ttf")) {
        std::cout << "Fonts can't be loaded" << std::endl;
    } else {
        std::cout << "Fonts have been loaded" << std::endl;
        m_text.setFont(m_font);
        m_outOfAmmoText.setFont(m_font);
    }

    m_text.setCharacterSize(60);
    m_text.setPosition(m_window->getSize().x - 140.f, m_window->getSize().y - 90.f);

    m_outOfAmmoText.setString("Out of Ammo !");
    m_outOfAmmoText.setColor(sf::Color::Red);
    m_outOfAmmoText.setCharacterSize(100);
    m_outOfAmmoText.setPosition(90.f, 350.f);

    m_tank = new Tank(10); //Creates a new Tank with 10 ammo
    m_tank->setPosition(0, 400);
    m_tank->setWindowResolution(m_window->getSize().x, m_window->getSize().y);
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
            }
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
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_window->getView().getCenter().x + m_viewSpeed <= (float)m_window->getSize().x/2) {
            sf::FloatRect visibleArea(0, 0, m_window->getSize().x, m_window->getSize().y);
            sf::View view = sf::View(visibleArea);
            view.setCenter(m_window->getView().getCenter().x + m_viewSpeed, m_window->getView().getCenter().y);
            m_window->setView(view);
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
        m_window->draw(m_text);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) { // Space bar pressed
            if (m_tank->ifFire()) {
                std::cout << "Fire !" << std::endl;
            } else if (m_tank->getAmmo() == 0) { // Shoot
                m_window->draw(m_outOfAmmoText);
            } 
		}

		for (int j(0); j < m_enemiesNumber; j++) {
	        if (!m_enemiesArray[j].isDead()) {
                m_enemiesArray[j].setWindowSize(m_window->getSize());
        	    m_window->draw(m_enemiesArray[j]);
        	    m_enemiesArray[j].move();
                if (m_tank->ifBullet()) {
                    if (
                        m_enemiesArray[j].getPosition().x + 100.f >= m_tank->getBullet().getPosition().x 
                        && 
                        m_tank->getBullet().getPosition().y >= m_enemiesArray[j].getPosition().y + m_tank->getBullet().getSize().y
                        &&
                        m_tank->getBullet().getPosition().y <= m_enemiesArray[j].getPosition().y + 100.f
                        ) {

                        m_enemiesArray[j].killEnemies();
                        std::cout << j << "Killed" << std::endl;
                        m_tank->killBullet();
                    }
                }
	    	} else {

		  	}
        }
        
        if (m_tank->ifBullet()) {
            m_window->draw(m_tank->getBullet());
            m_tank->BulletMove();
        }

        m_window->draw(m_text);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            if (m_tank->ifRecharge()) {
                std::cout << "Reload !" << std::endl;
            } else if (m_tank->getAmmo() == 0) {
                m_window->draw(m_outOfAmmoText); 
            }
        }

        m_window->display();
    }

    delete m_tank;
    m_tank = NULL;
}
