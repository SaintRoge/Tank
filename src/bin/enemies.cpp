#include "../lib/enemies.hpp"

Enemies::Enemies() {
  	m_speed = 2.f;
	m_isDead = false;
}

Enemies::~Enemies() {
	
}

void Enemies::move() {
  if (getPosition().x > 1000.f) {
    deleteEnemies();
  }
  setPosition(getPosition().x + m_speed, getPosition().y);
}

void Enemies::deleteEnemies() {
  m_isDead = true;
}

bool Enemies::isDead() {
  return m_isDead;
}
