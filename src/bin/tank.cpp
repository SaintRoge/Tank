#include "../lib/tank.hpp"

Tank::Tank(int ammo) {

	m_upSpeed = 12.f;
	m_downSpeed = -12.f;

	std::ifstream file("speedCoef.txt");

	if (file) {
		std::string speedCoef;
		std::getline(file, speedCoef);
		m_speedCoef = std::stof(speedCoef);
		m_upSpeed *= m_speedCoef;
		m_downSpeed *= m_speedCoef;

	} else {
		std::cout << "Oh shit, you can't open the file !" << std::endl;
	}

	m_TankXSize = 255;
	m_TankYSize = 160;
	m_distance = 300;

	m_fireTime = sf::seconds(1.f);
	m_rechargeTime = sf::seconds(0.2f);

	m_overTankEnabled = false;

	m_overTankSprite = new sf::Sprite(); 

	m_recharge = true;
	m_ifBullet = false;

	m_ammo = ammo;

	m_bullet = 0;

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
	if (up && getPosition().y - m_upSpeed > 0.f && getPosition().y < (float)m_windowResolutionY - m_TankYSize) {
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

			m_overTankSprite->setPosition(m_windowResolutionX - m_distance, (float)m_windowResolutionY + getPosition().y);
		} else {
			setPosition(sf::Vector2f(m_windowResolutionX - m_distance, (float)m_windowResolutionY - m_TankYSize));
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

			m_overTankSprite->setPosition(m_windowResolutionX - m_distance, 0);
		} else {
			setPosition(m_windowResolutionX - m_distance, 0.f);
		}
	}
	
}


bool Tank::ifFire() {
	if (ifAmmo()) {
		if (m_fireClock.getElapsedTime() >= m_fireTime && m_recharge) {
			m_fireClock.restart();
			m_rechargeClock.restart();
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

	if (getPosition().y + (float)m_TankYSize/2 < 0.f) {
		m_bullet = new Bullet(sf::Vector2f(m_windowResolutionX - m_distance + 20.f, m_windowResolutionY + (getPosition().y + (float)m_TankYSize/2)));
	} else if (getPosition().y + (float)m_TankYSize/2 > (float)m_windowResolutionY) {
		m_bullet = new Bullet(sf::Vector2f(m_windowResolutionX - m_distance + 20.f, getPosition().y + (float)m_TankYSize/2 - m_windowResolutionY));
	} else {
		m_bullet = new Bullet(sf::Vector2f(m_windowResolutionX - m_distance + 20.f, getPosition().y + (float)m_TankYSize/2));
	}
	setTankTexture(m_textureFire);
	m_overTankSprite->setTexture(m_textureFire);
	m_ifBullet = true;
	m_fireMusic.play();
	m_ammo--;
}

void Tank::BulletMove() {
	if (m_bullet->getPosition().x < -m_windowResolutionX || !m_ifBullet) {
		delete m_bullet;
		m_ifBullet = false;
	} else {
		m_bullet->move();
	}
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

bool Tank::ifBullet() {
	if (m_ifBullet) {
		return true;
	} else {
		return false;
	}
}

void Tank::recharge() {
	m_rechargeMusic.play();
	m_recharge = true;
	setTankTexture(m_texture);
	m_overTankSprite->setTexture(m_texture);
}

void Tank::setWindowResolution(int const x, int const y) {
	m_windowResolutionX = x;
	m_windowResolutionY = y;
	setPosition(m_windowResolutionX - m_distance, getPosition().y);
}

sf::Sprite Tank::getOverSprite() const {
	return *m_overTankSprite;
}

Bullet Tank::getBullet() const {
	return *m_bullet;

}

int Tank::getAmmo() const {
	return m_ammo;
}

void Tank::killBullet() {
	delete m_bullet;
	m_ifBullet = false;
}

void Tank::setAmmo(int const ammo) {
	m_ammo = ammo;
}

sf::Time Tank::getElapsedFireClockTime() const {
	return m_fireClock.getElapsedTime();
}

sf::Time Tank::getFireTime() const {
	return m_fireTime;
}