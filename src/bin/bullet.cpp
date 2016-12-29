#include "../lib/bullet.hpp"

Bullet::Bullet(sf::Vector2f position) {
	std::ifstream file("speedCoef.txt");
	if (file) {
        std::string speedCoef;
        std::getline(file, speedCoef);
        m_speedCoef = std::stof(speedCoef);
    } else {
        std::cout << "Oh shit, you can't open the file !" << std::endl;
    }
	m_position = position;
	m_BulletSize.x = 20.f;
	m_BulletSize.y = 10.f;

	m_speed = 50.f;

	setFillColor(sf::Color::Red);
	setPosition(m_position.x, m_position.y - m_BulletSize.y/2 );
	setSize(m_BulletSize);
}

Bullet::~Bullet() {

}

void Bullet::move() {
	setPosition(getPosition().x - m_speed * m_speedCoef, m_position.y);
}
