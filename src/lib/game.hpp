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

	void randomEnemie(int id);
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
	int m_politicalsNumber;

	float m_viewSpeed;
	float m_speedCoef;

	bool m_gameover;
	bool m_fullScreen;
	bool m_superBullet;

	Tank *m_tank;

	std::string m_killer;

	Enemies m_enemiesArray[6];
	std::vector<std::string> m_nameArray;
	std::vector<int> m_scoreArray;
	std::vector<sf::Sound*> m_musicArray;
	std::vector<sf::SoundBuffer*> m_bufferArray;
	std::vector<sf::Texture*> m_textureArray;
	std::vector<int> m_killedEnemies;

	sf::FloatRect m_visibleArea;

	sf::RenderWindow *m_window;

	sf::Sprite m_overSprite;

	sf::Clock m_gameClock;
	sf::Clock m_fullScreenClock;
	sf::Clock m_superBulletClock;

	sf::Time m_fireTime;
	sf::Time m_reloadTime;

	sf::Text m_text;
	sf::Text m_outOfAmmoText;
	sf::Text m_scoreText;
	sf::Text m_gameoverText;
	sf::Text m_normalViewText;
	sf::Text m_secondsText;
	sf::Font m_font;

	sf::Sprite m_life1;
	sf::Sprite m_life2;
	sf::Sprite m_life3;

	sf::Texture m_aliveHeart;
	sf::Texture m_deadHeart;
	sf::Texture m_defaultTexture;

	sf::Music m_music;
	sf::Sound m_deadMusic;
	sf::SoundBuffer m_deadMusicBuffer;

	sf::View m_view;

	sf::Vector2u m_windowSize;
};

#endif
