#ifndef BULLET_HPP 
#define BULLET_HPP 

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "enemies.hpp"
#include <iostream>
#include <string>

class Bullet : public sf::RectangleShape {
public:
	Bullet(sf::Vector2f position);
	~Bullet();

	void move();
	/*
	 * Needs nothing
	 * The bullet moves with m_speed speed
	 * Returns nothing
	 */

////////////////////////////////////////////////////////////////

	void setSpeed(float speed);
	/*
	 * Needs speed
	 * Set it
	 * Returns nothing 
	 */

private:
	sf::Vector2f m_position;
	sf::Vector2f m_BulletSize;

	float m_speed;
};

#endif //BULLET_HPP