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

private:
	sf::Texture m_texture;

	std::string m_img;
};

#endif //TANK_HPP