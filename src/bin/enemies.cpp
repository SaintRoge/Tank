#include "../lib/enemies.hpp"

Enemies::Enemies() {

	std::ifstream file("speedCoef.txt");

    if (file) {
        std::string speedCoef;
        std::getline(file, speedCoef);
        m_speedCoef = std::stof(speedCoef);
    } else {
        std::cout << "Oh shit, you can't open the file !" << std::endl;
        m_speedCoef = 1;
    }

    m_humanKill = false;
  	m_speed = 0;
	m_isDead = false;
	m_score = 0;
	m_windowSize.x = 1200;
	m_windowSize.y = 800;
}

Enemies::~Enemies() {
	
}

void Enemies::move() {
  	if (getPosition().x > m_windowSize.x - 100) {
    	killEnemies(false);
  	} else {
        setPosition(getPosition().x + m_speed, getPosition().y);
        //std::cout << m_name << " moves for x: " << getPosition().x << " y: "<< getPosition().y << " with the speed of " << m_speed << std::endl;
    }
  	
}

void Enemies::killEnemies(bool humanKill) {
 	 m_isDead = true;
     m_humanKill = humanKill;
     m_deathMusic.play();
}

bool Enemies::isDead() const {
  	return m_isDead;
}

bool Enemies::isHumanKill() const {
    return m_humanKill;
}

void Enemies::setWindowSize(sf::Vector2u size) {
	   m_windowSize = size;
}

void Enemies::setName(std::string name) {
    m_name = name;
}

void Enemies::setScore(int score) {
    m_score = score;
}

int Enemies::getScore() const {
  	return m_score;
}

std::string Enemies::getName() const {
    return m_name;
}

void Enemies::setSpeed(float speed) {
    m_speed = speed * m_speedCoef;
}

float Enemies::getSpeed() const {
    return m_speed;
}

void Enemies::setDeathMusic() {
    if (!m_deathMusic.openFromFile("snd/" + m_name + ".mp3")) {
        std::cout << "Sorry, the music can't be loaded for " << m_name << std::endl;
    } else {
        std::cout << "The music has been loaded" << std::endl;
    }
}