#include "../lib/tank.hpp"

Tank::Tank() {
	m_leftSpeed = 3.f;
	m_rightSpeed = -2.f;

  	m_img = "img/Tank-GTAA.png";
	  
	if (!m_texture.loadFromFile(m_img, sf::IntRect(0, 0, 255, 160))) {
	    std::cout << "Sorry, " << m_img << " can't be loaded." << std::endl;
	} else {
		std::cout << m_img << " has been loaded." << std::endl;
	}

	setTankTexture(m_texture);
}

Tank::~Tank() {

}	

void Tank::setTankTexture(sf::Texture const& texture) {
	setTexture(texture);
}

sf::Vector2f Tank::move(bool forward) {
	if (forward) {
		setPosition(getPosition() - sf::Vector2f(m_leftSpeed, 0.f));
	} else {
		setPosition(getPosition() - sf::Vector2f(m_rightSpeed, 0.f));
	}
}
