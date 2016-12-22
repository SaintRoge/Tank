#include "../lib/tank.hpp"

Tank::Tank() {

	m_upSpeed = 3.f;
	m_downSpeed = -3.f;

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

void Tank::move(bool up) {
	if (up) {
		setPosition(getPosition() - sf::Vector2f(0.f, m_upSpeed));
	} else {
		setPosition(getPosition() - sf::Vector2f(0.f, m_downSpeed));
	}
}

void Tank::fire() {

}
