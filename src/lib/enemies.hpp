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
  	void killEnemies();
    /*
     * Needs nothing
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

  /////////////////////////////////////////////////

	int getScore() const;
    /*
     * Needs nothing
	 * Says to you the enemie score
	 * Returns that
	 */

	std::string getName() const;
	/*
     * Needs nothing
	 * Says to you the enemie name
	 * Returns that
	 */

	sf::Texture getVTexture() const;
	/*
     * Needs nothing
	 * Says to you the enemie texture
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

  	void setVTexture(sf::Texture texture);
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

  
  
private:
	int m_speed;
	int m_score;

	float m_speedCoef;
	  
	bool m_isDead; 

	std::string m_name;

	sf::Vector2u m_windowSize;
	sf::Texture m_texture;
};

#endif //ENNEMIES_HPP
