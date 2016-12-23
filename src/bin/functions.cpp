#include "../lib/functions.hpp"

sf::Texture randomTexture() {
	sf::Texture texture;
	int imgNumber(2);
	std::string imgArray[imgNumber];
	imgArray[0] = "boutin.png";
	imgArray[1] = "Fillon.png";
	texture.loadFromFile("img/" + imgArray[std::rand() % imgNumber], sf::IntRect(10, 10, 100, 100));
	return texture;

}

