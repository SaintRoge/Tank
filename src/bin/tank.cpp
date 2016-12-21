#include "../lib/tank.hpp"

Tank::Tank() {
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

sf::Vector2f move(sf::Vector2f direction) {

}
