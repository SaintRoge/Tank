#include "../lib/tank.hpp"

Tank::Tank() {
  	m_img = "img/Tank-GTAA.png";
	  
	if (!setTankImg(&m_texture, m_img)) {
	    std::cout << "Sorry, " << m_img << " can't be load" << std::endl;
	}

	if (!m_texture.create(145, 229)) {
	    std::cout << "Sorry, the texture can't be created" << std::endl;
	}

	setTankTexture(&m_texture);
}

Tank::~Tank() {
}	

bool Tank::setTankImg(sf::Texture *texture, std::string img) {
	if (!texture->loadFromFile(img, sf::IntRect(-100, -100, 32, 32))) {
		return false;
	} else {
		return true;
	}
}

void Tank::setTankTexture(sf::Texture *texture) {
	setTexture(*texture);
}
