#include "../lib/enemies.hpp"

Enemies::Enemies() {
	srand(time(NULL));
  	m_speed = (float) (std::rand() % 926 + 75)/100;
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
  	setPosition(getPosition().x + m_speed, getPosition().y);
}

void Enemies::killEnemies() {
 	 m_isDead = true;
}

bool Enemies::isDead() {
  	return m_isDead;
}

void Enemies::setWindowSize(sf::Vector2u size) {
	m_windowSize = size;
}

int Enemies::getScore() const {
  	return m_score;
}
