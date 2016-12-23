#include "../lib/bullet.hpp"

Bullet::Bullet(sf::Vector2f position) {
	m_position = position;
	m_BulletSize.x = 20.f;
	m_BulletSize.y = 10.f;

	m_speed = 15.f;

	setFillColor(sf::Color::Red);
	setPosition(m_position.x, m_position.y - m_BulletSize.y/2 );
	setSize(m_BulletSize);
}

Bullet::~Bullet() {

}

void Bullet::move() {
	
}