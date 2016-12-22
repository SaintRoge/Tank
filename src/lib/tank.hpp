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

	void move(bool const up);
	/*
	 * Needs direction
	 * The Tank moves
	 * Returns nothing
	 */
	void overMove(bool const up, bool const reverse);
	/*
	 * Needs direction
	 * Move your tank to the opposite side when it comes out the borders
	 * Returns nothing
	 */

///////////////////////////////////////////////////////////////////////

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
	bool isOverEnabled() const;
	/*
	 * Needs nothing
	 * Says if the over tank mode is enabled
	 * Returns it value
	 */

///////////////////////////////////////////////////////////////////////

	sf::Sprite getOverSprite() const;
	/*
	 * Needs nothing
	 * Gives you the Over Sprite
	 * Returns Over Sprite
	 */

///////////////////////////////////////////////////////////////////////

	void setTankTexture(sf::Texture const& texture);
	/* 
	 * Needs texture
	 * Set the Tank Sprite texture
	 * Returns nothing
	 */

	void setWindowResolution(int const x, const int y);
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
	//sf::Texture m_overTankTexture;

	sf::Sprite *m_overTankSprite;

	sf::Music m_fireMusic;
	sf::Music m_outOfAmmoMusic;

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

	bool m_overTankEnabled; //If the Tank is out the borders
};

#endif //TANK_HPP