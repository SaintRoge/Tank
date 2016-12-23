#ifndef BULLET_HPP 
#define BULLET_HPP 

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>

class Bullet : public sf::RectangleShape {
public:
	Bullet(sf::Vector2f position);
	~Bullet();

private:
	sf::Vector2f m_position;
};

#endif //BULLET_HPP