#include "../lib/tank.hpp"

Tank::Tank() {
  	m_img = "img/Tank-GTAA.png";
	  
	if (!m_texture.loadFromFile(m_img, sf::IntRect(0, 0, 32, 32))) {
	    std::cout << "Sorry, " << m_img << " can't be loaded." << std::endl;
	} else {
		std::cout << m_img << " has been loaded." << std::endl;
	}

	if (!m_texture.create(255, 160)) {
	    std::cout << "Sorry, the texture can't be created." << std::endl;
	} else {
		std::cout << "The texture has been created." << std::endl;
	}

	setTankTexture(m_texture);
}

Tank::~Tank() {

}	

void Tank::setTankTexture(sf::Texture const& texture) {
	setTexture(texture);
}
