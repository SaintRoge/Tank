#include "../lib/bullet.hpp"

Bullet::Bullet(sf::Vector2f position) {
	m_position = position;
	setPosition(m_position);
	std::cout << "Bullet created at : " << m_position.x << ", " << m_position.y << std::endl;
}

Bullet::~Bullet() {

}