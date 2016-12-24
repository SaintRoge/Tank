#include "../lib/enemies.hpp"

Enemies::Enemies() {
  	m_speed = 2.f;
	m_isDead = false;
	m_score = 0;
}

Enemies::~Enemies() {
	
}

void Enemies::move() {
  	if (getPosition().x > 1100.f) {
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

int Enemies:: getScore() const {
  	return m_score;
}
