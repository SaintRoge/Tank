#include "../lib/enemies.hpp"

Enemies::Enemies() {
	srand(time(NULL));
	std::ifstream file("speedCoef.txt");

    if (file) {
        std::string speedCoef;
        std::getline(file, speedCoef);
        m_speedCoef = std::stof(speedCoef);
    } else {
        std::cout << "Oh shit, you can't open the file !" << std::endl;
        m_speedCoef = 1;
    }
  	m_speed = (float) ((std::rand() % 1500 + 100)/100) * m_speedCoef;
	m_isDead = false;
	m_score = 0;
	m_windowSize.x = 1200;
	m_windowSize.y = 800;
}

Enemies::~Enemies() {
	
}

void Enemies::move() {
  	if (getPosition().x > m_windowSize.x - 100) {
   		m_score++;
    	killEnemies();
  	} else {
        setPosition(getPosition().x + m_speed, getPosition().y);
    }
  	
}

void Enemies::killEnemies() {
 	 m_isDead = true;
}

bool Enemies::isDead() const {
  	return m_isDead;
}

void Enemies::setWindowSize(sf::Vector2u size) {
	   m_windowSize = size;
}

void Enemies::setName(std::string name) {
    m_name = name;
}

void Enemies::setVTexture(sf::Texture texture) {
    m_texture = texture;
    setTexture(m_texture);
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

sf::Texture Enemies::getVTexture() const {
    return m_texture;
}

void Enemies::setSpeed(float speed) {
    m_speed = speed * m_speedCoef;
}
