#include "../lib/functions.hpp"

sf::Texture randomTexture() {
	sf::Texture texture;
	std::string imgArray[] = {"boutin", "Fillon", "macron", "valls", "juppé"};
	texture.loadFromFile("img/" + imgArray[std::rand() % (sizeof(imgArray)/sizeof(*imgArray))] + ".png", sf::IntRect(0, 0, 100, 100));
	return texture;

}

