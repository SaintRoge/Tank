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
  
  
private:
  int m_speed;
  int m_score;
  
  bool m_isDead; 
};

#endif //ENNEMIES_HPP
