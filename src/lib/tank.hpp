#ifndef TANK_HPP 
#define TANK_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class Tank : public sf::Sprite {
public:
	Tank();
	~Tank();
	bool setTankImg(sf::Texture *texture, std::string img);
	void setTankTexture(sf::Texture *texture);

private:
	sf::Texture m_texture;

	std::string m_img;
};

#endif //TANK_HPP