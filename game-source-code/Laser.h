/**
 * @class Laser
 * @brief The class encapsulating the functionality of a Laser within the Centepede Wars Game environment.
 * @author Rashaad Cassim 1099797 and Jason Parry 1046955
 * @file Laser.h
 */
#ifndef LASER_H
#define LASER_H

#include "Entity.h"
#include "Movable.h"
#include <tuple>

class Laser: public Entity, public Movable {
public:
/**
 * @brief Default constructor.
 */
	Laser();
/**
 * @brief Constructor for a Laser object at a position, from where it was shot.
 * @param x is the initial position in the x plane of the Laser.
 * @param y is the initial position in the y plane of the Laser.
 */
	Laser(int x, int y);
	
/**
 * @brief Moves the Laser object by changing it's position.
 * @param horizontal is the distance the Laser object will move in the x plane.
 * @param vertical is the distance the Laser object will move in the y plane.
 */
	void move(int horizontal, int vertical) override;
/**
 * @brief Destructor.
 */
	
	~Laser();
	
private:
	int _moveStep = 16;
	
};

#endif // LASER_H
