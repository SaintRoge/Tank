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
#include <fstream>

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
	void gameover();
	/*
	 * Needs nothing
	 * The game is over
	 * Returns nothing
	 */
	void resize(); 
	/*
	 * Needs nothing
	 * All the components are resized
	 * Returns nothing
	 */

////////////////////////////////////////////////////////////////////

	sf::Texture randomTexture(int id);
	/*
	 * Needs id
	 * Creates a random enemie texture
	 * Returns it
	 */
  
private:
	int m_enemiesNumber;
	int m_enemiesScore;
	int m_score;
	int m_maximumEnemiesScore;

	float m_viewSpeed;
	float m_speedCoef;

	bool m_gameover;
	bool m_fullScreen;

	Tank *m_tank;

	std::string m_killer;

	std::vector<sf::Texture> m_textureArray;
	std::vector<Enemies> m_enemiesArray;
	std::vector<std::string> m_namesArray;

	sf::FloatRect m_visibleArea;

	sf::RenderWindow *m_window;

	sf::Sprite m_overSprite;

	sf::Clock m_gameClock;
	sf::Clock m_fullScreenClock;

	sf::Text m_text;
	sf::Text m_outOfAmmoText;
	sf::Text m_scoreText;
	sf::Text m_gameoverText;
	sf::Font m_font;

	sf::Sprite m_life1;
	sf::Sprite m_life2;
	sf::Sprite m_life3;

	sf::Texture m_aliveHeart;
	sf::Texture m_deadHeart;

	sf::Music m_music;
	sf::Music m_deadMusic;

	sf::Vector2u m_windowSize;
};

#endif
