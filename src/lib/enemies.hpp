#ifndef ENNEMIES_HPP
#define ENNEMIES_HPP 

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>

class Enemies : public sf::Sprite {
public:
	Enemies();
	~Enemies();

	void setTexture(sf::Texture const& texture);

private:

};

#endif //ENNEMIES_HPP