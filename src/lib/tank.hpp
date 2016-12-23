#ifndef TANK_HPP 
#define TANK_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string> 

#include "bullet.hpp"
#include "ennemies.hpp"

class Tank : public sf::Sprite {
public:
	Tank(int ammo);
	~Tank();

///////////////////////////////////////////////////////////////////////

	void move(bool const up);
	/*
	 * Needs direction
	 * The Tank moves
	 * Returns nothing
	 */
	void overMove(bool const up);
	/*
	 * Needs direction
	 * Move your tank to the opposite side when it comes out the borders
	 * Returns nothing
	 */
	void BulletMove();
	/*
	 * Needs nothing
	 * call move() in m_bullet
	 * returns nothing
	 */

///////////////////////////////////////////////////////////////////////

	bool ifFire();
	/*
	 * Needs nothing
	 * Call fire
	 * Returns if he can fire
	 */
	bool ifRecharge();
	/* Needs nothing
	 * Says to you if you can reload
	 * Returns if you can reload
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
	bool ifBullet();
	/*
	 * Needs nothing
	 * Says if you can get the bullet
	 * Returns that
	 */

///////////////////////////////////////////////////////////////////////

	sf::Sprite getOverSprite() const;
	/*
	 * Needs nothing
	 * Gives you the Over Sprite
	 * Returns Over Sprite
	 */
	Bullet getBullet() const;
	/*
	 * Needs nothing
	 * If the bullet exists givs you the bullet
	 * Returns bullet
	 */
	int getAmmo() const;
	/* Needs nothing
	 * Gives you the number of ammo
	 * Returns ammo
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
	void recharge();
	/*
	 * Needs nothig
	 * The tank reload
	 * Returns nothing
	 */

private:
	sf::Texture m_texture;
	sf::Texture m_textureFire;

	sf::Sprite *m_overTankSprite;

	sf::Music m_fireMusic;
	sf::Music m_outOfAmmoMusic;
	sf::Music m_rechargeMusic;

	sf::Time m_fireTime;
	sf::Time m_rechargeTime;
	sf::Clock m_rechargeClock;
	sf::Clock m_fireClock;

	std::string m_img;
	std::string m_imgFire;

	Bullet *m_bullet;

	int m_ammo;
	int m_windowResolutionX;
	int m_windowResolutionY;
	int m_TankXSize;
	int m_TankYSize;

	float m_upSpeed;
	float m_downSpeed;

	bool m_overTankEnabled; //If the Tank is out the borders
	bool m_recharge;
	bool m_ifBullet;
};

#endif //TANK_HPP