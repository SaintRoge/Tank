#include "../lib/tank.hpp"

Tank::Tank() {

	m_upSpeed = 7.f;
	m_downSpeed = -7.f;
	m_TankXSize = 255;
	m_TankYSize = 160;

	m_fireTime = sf::seconds(1.f);
	m_rechargeTime = sf::seconds(0.2f);

	m_overTankEnabled = false;

	m_overTankSprite = new sf::Sprite();

	m_recharge = true;

	m_ammo = 10;

  	m_img = "img/Tank-GTAA.png";
  	m_imgFire = "img/Tank-GTAA-fire.png";

  	if (!m_fireMusic.openFromFile("snd/fire.wav") || !m_outOfAmmoMusic.openFromFile("snd/out-of-ammo.wav") || !m_rechargeMusic.openFromFile("snd/recharge.wav")) {
        std::cout << "Sorry, sounds can't be loaded" << std::endl;
    } else {
        std::cout << "Sounds have been loaded" << std::endl;
    }
	  
	if (!m_texture.loadFromFile(m_img, sf::IntRect(0, 0, m_TankXSize, m_TankXSize)) || !m_textureFire.loadFromFile(m_imgFire, sf::IntRect(0, 0, m_TankXSize, m_TankXSize))) {
	    std::cout << "Sorry, " << m_img << " and " << m_imgFire << "can't be loaded." << std::endl;
	} else {
		std::cout << m_img << " and " << m_imgFire << " have been loaded." << std::endl;
	}

	setTankTexture(m_texture);
	m_overTankSprite->setTexture(m_texture);

	m_rechargeClock.restart();
}

Tank::~Tank() {

}	

void Tank::setTankTexture(sf::Texture const& texture) {
	setTexture(texture);
}

void Tank::move(bool up) {
	if (up && getPosition().y - m_upSpeed > 0.f && getPosition().y - m_downSpeed < (float)m_windowResolutionY - m_TankYSize) {
		setPosition(getPosition() - sf::Vector2f(0.f, m_upSpeed));
		if (m_overTankEnabled) {
			m_overTankEnabled = false;
		}
	} else if (!up && getPosition().y - m_downSpeed < (float)m_windowResolutionY - m_TankYSize && getPosition().y - m_upSpeed > 0.f){
		setPosition(getPosition() - sf::Vector2f(0.f, m_downSpeed));
		if (m_overTankEnabled) {
			m_overTankEnabled = false;
		}
	} else if (up && getPosition().y - m_upSpeed <= 0.f) {
		setPosition(getPosition() - sf::Vector2f(0.f, m_upSpeed));
		overMove(true);
	} else if (!up && getPosition().y - m_downSpeed >= m_windowResolutionY - m_TankYSize) {
		setPosition(getPosition() - sf::Vector2f(0.f, m_downSpeed));
		overMove(false);
	} else if (up && getPosition().y - m_downSpeed >= m_windowResolutionY - m_TankYSize) {
		setPosition(getPosition() - sf::Vector2f(0.f, m_upSpeed));
		overMove(false);
	} else {
		setPosition(getPosition() - sf::Vector2f(0.f, m_downSpeed));
		overMove(true);
	}
}

void Tank::overMove(bool up) {
	if (!m_overTankEnabled) {
		m_overTankEnabled = true;
	}

	if (up) { // Moves up
		if (getPosition().y > -m_TankYSize) {

			m_overTankSprite->setTextureRect(
				sf::IntRect(
					0,
					0, 
					m_TankXSize, 
					-(m_TankYSize + (getPosition().y - m_TankYSize))
				)
			);

			m_overTankSprite->setPosition(getPosition().x, (float)m_windowResolutionY + getPosition().y);

			//std::cout << m_overTankSprite->getTextureRect().height << "   " << m_overTankSprite->getPosition().y << "    " << std::endl;
		} else {
			setPosition(sf::Vector2f(getPosition().x, (float)m_windowResolutionY - m_TankYSize));
		}
	} else {
		if (getPosition().y < m_windowResolutionY) {

			m_overTankSprite->setTextureRect(
				sf::IntRect(
					0, 
					m_windowResolutionY - getPosition().y, 
					m_TankXSize, 
					m_TankYSize - (m_windowResolutionY - getPosition().y)
					)
				);

			m_overTankSprite->setPosition(getPosition().x, 0);

			//std::cout << m_overTankSprite->getTextureRect().height << "   " << m_overTankSprite->getPosition().y << std::endl;
		} else {
			setPosition(getPosition().x, 0.f);
		}
	}
	
}


bool Tank::ifFire() {
	if (ifAmmo()) {
		if (m_fireClock.getElapsedTime() >= m_fireTime && m_recharge) {
			m_fireClock.restart();
			fire();
			m_recharge = false;
			return true;
		} else {
			m_outOfAmmoMusic.play();
			std::cout << "Reload before fire !" << std::endl;
			return false;
		}
	} else {
		m_outOfAmmoMusic.play();
		std::cout << "Out of ammo !" << std::endl;
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

bool Tank::isOverEnabled() const {
	return m_overTankEnabled;
}

void Tank::fire() {
	setTankTexture(m_textureFire);
	m_overTankSprite->setTexture(m_textureFire);
	m_fireMusic.play();
	m_ammo--;
}

bool Tank::ifRecharge() {
	if (m_ammo > 0 && m_rechargeClock.getElapsedTime() >= m_rechargeTime && !m_recharge) {
		recharge(); 
		m_rechargeClock.restart();
		return true;
	} else if (m_ammo <= 0) {
		m_outOfAmmoMusic.play();
		return false;
	} else if (m_recharge) {
		std::cout << "You have arleady reloaded" << std::endl;
		return false;
	} else {
		std::cout << "Wait !" << std::endl;
		return false;
	}
}

void Tank::recharge() {
	m_rechargeMusic.play();
	m_recharge = true;
	setTankTexture(m_texture);
	m_overTankSprite->setTexture(m_texture);
}

void Tank::setWindowResolution(int x, int y) {
	m_windowResolutionX = x;
	m_windowResolutionY = y;
}

sf::Sprite Tank::getOverSprite() const {
	return *m_overTankSprite;
}

int Tank::getAmmo() const {
	return m_ammo;
}