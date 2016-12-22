#include "../lib/tank.hpp"

Tank::Tank() {

	m_upSpeed = 7.f;
	m_downSpeed = -7.f;
	m_TankXSize = 255;
	m_TankYSize = 160;

	m_fireTime = sf::seconds(1.f);

	m_ammo = 10;

  	m_img = "img/Tank-GTAA.png";

  	if (!m_fireMusic.openFromFile("snd/fire.wav")) {
        std::cout << "Sorry, the sounds can't be loaded" << std::endl;
    } else {
        std::cout << "The sounds have been loaded" << std::endl;
    }
	  
	if (!m_texture.loadFromFile(m_img, sf::IntRect(0, 0, m_TankXSize, m_TankXSize))) {
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
	if (up && getPosition().y - m_upSpeed > 0.f) {
		setPosition(getPosition() - sf::Vector2f(0.f, m_upSpeed));
	} else if (!up && getPosition().y - m_downSpeed < (float)m_windowResolutionY - m_TankYSize){
		setPosition(getPosition() - sf::Vector2f(0.f, m_downSpeed));
	} 
}

bool Tank::ifFire() {
	if (ifAmmo()) {
		if (m_fireClock.getElapsedTime() >= m_fireTime) {
			m_fireClock.restart();
			fire();
			return true;
		}
		else {
			std::cout << "Recharge !" << std::endl;
			return false;
		}
	} else {
		std::cout << "Have no ammo !" << std::endl;
		return false;
	}
}

bool Tank::ifAmmo() {
	if (m_ammo == 0) {
		return false;
	} else if (m_ammo < 0) {
		m_ammo = 0;
		return false;
	} else {
		return true;
	}
}

void Tank::fire() {
	m_fireMusic.play();
	m_ammo--;
}

void Tank::setWindowResolution(int x, int y) {
	m_windowResolutionX = x;
	m_windowResolutionY = y;
}

