/**
 * @class DDTBomb
 * @brief The DDTBomb class encapsulates the DDTBomb entity within the Centipede Wars game environment.
 * @author Rashaad Cassim 1099797 and Jason Parry 1046955
 * @file DDTBomb.h
 */
#ifndef DDTBOMB_H
#define DDTBOMB_H
#include "Entity.h"
#include <tuple>
class DDTBomb: public Entity {
public:

/**
 * @brief Constructor for a DDTBomb object.
 * @param x is the initial x position of the DDTBomb.
 * @param y is the initial y position of the DDTBomb.
 */
	DDTBomb(int x,int y);
/**
 * @brief Destructor.
 */
	~DDTBomb();
	
/**
 * @brief Returns the DDTBomb objects' blast radius.
 */
	int getBlastRadius();
	
/**
 * @brief Returns true if the DDTBomb object has been hit by a Laser.
 */
	
	bool hasExploded();
	
/**
 * @brief Sets the DDTBombs status as exploded.
 */
	
	void setExploded();
	
/**
 * @brief Incriments the number of timesteps that the DDTBomb has been displayed for since it has been hit by a Laser.
 */
	
	void incrimentTime();
	
/**
 * @brief Returns the number of timesteps that a DDTBomb has been displayed since it was hit.
 */
	
	int getTime();
	
private:
	std::tuple<int,int> _pos;
	int _blastRadius=80;
	bool _exploded=false;
	int _time=0;
};

#endif // DDTBOMB_H
