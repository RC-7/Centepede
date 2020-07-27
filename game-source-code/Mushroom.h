/**
 * @class Mushroom
 * @brief The class encapsulating the functionality of a Mushroom within the Centepede Wars game environment.
 * @author Rashaad Cassim 1099797 and Jason Parry 1046955
 * @file Mushroom.h
 */
#ifndef MUSHROOM_H
#define MUSHROOM_H
#include "Entity.h"
#include <tuple>

class Mushroom: public Entity {
public:

/**
 * @brief Constructor for a Mushroom object initialised at a position.
 * @param x is the Mushroom objects position in the x plane.
 * @param y is the Mushroom objects position in the y plane.
 */

	Mushroom(int x, int y);
	
/**
 * @brief Default Destructor.
 */
	~Mushroom();
/**
 * @brief Decreases the Mushroom objects health.
 */
	
	void decreaseHealth();
	
/**
 * @brief Returns true if the Mushroom object has a non-zero health.
 */
	
	bool hasHealth();
	
/**
 * @brief Returns the health of a Mushroom object.
 */
	
	int getHealth() override;
	
private:
	 std::tuple<int,int> _pos;
	 int _health=4;

};

#endif // MUSHROOM_H
