#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h>
#include <vector>

#include "functions.hpp"
#include "tank.hpp"
#include "bullet.hpp"
#include "enemies.hpp"

class Game {
public:
	Game(sf::RenderWindow *window);
	~Game();
	void start();
	/*
	 * Needs nothing
	 * Starts the game
	 * Returns nothing
	 */
  
private:
	int m_enemiesNumber;
	int m_enemiesScore;
	int m_score;
	float m_viewSpeed;

	Tank *m_tank;

	std::vector<sf::Texture> m_textureArray;
	std::vector<Enemies> m_enemiesArray;

	sf::RenderWindow *m_window;

	sf::Sprite m_overSprite;

	sf::Text m_text;
	sf::Text m_outOfAmmoText;
	sf::Text m_scoreText;
	sf::Font m_font;

	sf::Music m_music;

	sf::Vector2u m_windowSize;
};

#endif
