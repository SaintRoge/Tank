#ifndef ENNEMIES_HPP
#define ENNEMIES_HPP 

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h>
#include <fstream>

class Enemies : public sf::Sprite {
public:
	Enemies();
	~Enemies();

  	void move();
	/*
	 * Needs nothing
	 * The enemie moves
	 * Returns nothing
	 */
  	void killEnemies(bool humanKill);
    /*
     * Needs the killer
	 * Delete this
	 * Returns nothing
	 */

  /////////////////////////////////////////////////

  	bool isDead() const;
    /*
     * Needs nothing
     * Says to you if the enemie is dead
     * Returns that
     */
  	bool isHumanKill() const;
  	/*
  	 * Needs nothing
  	 * Says if the kill was from the user
  	 * Returns bool
  	 */

  /////////////////////////////////////////////////

	int getScore() const;
    /*
     * Needs nothing
	 * Says to you the enemie score
	 * Returns that
	 */

	float getSpeed() const;
	/*
     * Needs nothing
	 * Says to you the enemie speed
	 * Returns that
	 */

	std::string getName() const;
	/*
     * Needs nothing
	 * Says to you the enemie name
	 * Returns that
	 */

  /////////////////////////////////////////////////

  	void setWindowSize(sf::Vector2u size);
  	/*
  	 * Needs size
  	 * Set it
  	 * Returns nothing
  	 */
  	void setSpeed(float speed);
	/*
	 * Needs speed
	 * Set it
	 * Returns nothing 
	 */ 

  	void setName(std::string name);
  	/*
	 * Needs the enemie texture
	 * Set it
	 * Returns nothing 
	 */ 

  	void setScore(int score);
  	/*
	 * Needs the enemie score
	 * Set it
	 * Returns nothing 
	 */ 

  	void setDeathMusic();
  	/*
  	 * Needs nothing
  	 * Says to the enemie that he can load the music
  	 * Returns nothing
  	 */

  
  
private:
	int m_score;

	float m_speedCoef;
	float m_speed;
	  
	bool m_isDead; 
	bool m_humanKill;

	std::string m_name;

	sf::Vector2u m_windowSize;

	sf::Music m_deathMusic;
};

#endif //ENNEMIES_HPP
