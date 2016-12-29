#include "../lib/enemies.hpp"

Enemies::Enemies() {
	srand(time(NULL));
	std::ifstream file("speedCoef.txt");

    if (file) {
        std::string speedCoef;
        std::getline(file, speedCoef);
        m_speedCoef = std::stof(speedCoef);
    } else {
        std::cout << "Oh shit, you can't open the file !" << std::endl;
    }
  	m_speed = (float) (std::rand() % 1500 + 100)/100;
	m_isDead = false;
	m_score = 0;
	m_windowSize.x = 1200;
	m_windowSize.y = 800;
}

Enemies::~Enemies() {
	
}

void Enemies::move() {
  	if (getPosition().x > m_windowSize.x - 100) {
   		 m_score++;
    	killEnemies();
  	}
  	setPosition(getPosition().x + m_speed * m_speedCoef, getPosition().y);
}

void Enemies::killEnemies() {
 	 m_isDead = true;
}

bool Enemies::isDead() const {
  	return m_isDead;
}

void Enemies::setWindowSize(sf::Vector2u size) {
	m_windowSize = size;
}

int Enemies::getScore() const {
  	return m_score;
}

void Enemies::setSpeed(float speed) {
	m_speed = speed;
}
