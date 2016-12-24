#ifndef ENNEMIES_HPP
#define ENNEMIES_HPP 

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h>

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

  	bool isDead();
    /*
     * Needs nothing
     * Says to you if the enemie is dead
     * Returns that
     */

  /////////////////////////////////////////////////

	int getScore() const;
    /*
     * Needs noyhing
	 * Says to you the enemie score
	 * Returns that
	 */

  /////////////////////////////////////////////////

  	void setWindowSize(sf::Vector2u size);
  	/*
  	 * Needs size
  	 * Set it
  	 * Returns nothing
  	 */
  
  
private:
	int m_speed;
	int m_score;
	  
	bool m_isDead; 

	sf::Vector2u m_windowSize;
};

#endif //ENNEMIES_HPP
