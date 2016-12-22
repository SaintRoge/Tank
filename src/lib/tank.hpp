#ifndef TANK_HPP 
#define TANK_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class Tank : public sf::Sprite {
public:
	Tank();
	~Tank();
	void setTankTexture(sf::Texture const& texture);
	/* 
	 * Needs texture
	 * Set the Tank Sprite texture
	 * Returns nothing
	 */
	void move(bool up);
	/*
	 * Needs speed and direction
	 * The Tank moves
	 * Returns nothing
	 */
	void fire();
	/*
	 * Needs nothing
	 * The tank shoots
	 * Returns nothing
	 */

private:
	sf::Texture m_texture;

	std::string m_img;

	float m_upSpeed;
	float m_downSpeed;
};

#endif //TANK_HPP