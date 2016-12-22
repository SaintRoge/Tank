#ifndef TANK_HPP 
#define TANK_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

class Tank : public sf::Sprite {
public:
	Tank();
	~Tank();

///////////////////////////////////////////////////////////////////////

	void setTankTexture(sf::Texture const& texture);
	/* 
	 * Needs texture
	 * Set the Tank Sprite texture
	 * Returns nothing
	 */
	void move(bool up);
	/*
	 * Needs speed and direction
	 * The Tank moves
	 * Returns nothing
	 */
	bool ifFire();
	/*
	 * Needs nothing
	 * Call fire
	 * Returns if he can fire
	 */
	bool ifAmmo();
	/*
	 * Needs nothing
	 * Says if you have ammo
	 * Returns false if you haven not ammo
	 */

///////////////////////////////////////////////////////////////////////

	void setWindowResolution(int x, int y);
	/* 
	 * Needs window resolution (x and y)
	 * Set it
	 * Returns nothing
	 */

protected:
	void fire();
	/*
	 * Needs nothig
	 * The tank shoot
	 * Returns nothing
	 */

private:
	sf::Texture m_texture;
	sf::Music m_fireMusic;
	sf::Time m_fireTime;
	sf::Clock m_fireClock;

	std::string m_img;

	int m_ammo;
	int m_windowResolutionX;
	int m_windowResolutionY;
	int m_TankXSize;
	int m_TankYSize;

	float m_upSpeed;
	float m_downSpeed;
};

#endif //TANK_HPP