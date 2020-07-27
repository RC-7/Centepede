/**
 * @class Collision
 * @brief The Collision class is an encapsulation of the responsibility to determine if two objects have collided during a time-step
 * @author Rashaad Cassim 1099797 and Jason Parry 1046955
 * @file Collision.h
 */
#ifndef COLLISION_H
#define COLLISION_H
#include <SFML/Graphics.hpp>
#include <vector>

class Collision
{
public:
/**
 * @brief Default Constructor.
 */

	Collision();
/**
 * @brief Default Destructor.
 */
	
	~Collision();
	/**
 * @brief Determines if two objects have collided during a time-step.
 * @param initialPos1 is a vector of the first objects position before and after the time-step.
 * @param initialPos2 is a vector of the second objects position before and after the time-step.
 */
	bool checkCollision(std::vector<std::tuple<int,int>> initialPos1,std::vector<std::tuple<int,int>> initialPos2);

};

#endif // COLLISION_H
