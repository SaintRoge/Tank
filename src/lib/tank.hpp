#ifndef TANK_HPP 
#define TANK_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class Tank : public sf::Sprite {
public:
	Tank();
	~Tank();
	static bool setTankImg(sf::Texture *texture, std::string img);
	static void setTankTexture(sf::Texture *texture);

private:
	sf::Texture m_texture;

	std::string m_img;
};

#endif //TANK_HPP