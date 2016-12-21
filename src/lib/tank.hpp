#ifndef TANK_HPP 
#define TANK_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class Tank : public sf::Sprite {
public:
	Tank();
	~Tank();
	bool setImg(std::string img);
	bool setTexture(sf::Texture *texture);

private:
	sf::Texture m_texture;

	std::string m_img;
};

#endif //TANK_HPP