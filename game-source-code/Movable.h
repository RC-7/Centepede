/**
 * @class Movable
 * @brief  encapsulates the ability to move that certain Entity objects possess.
 * @author Rashaad Cassim 1099797 and Jason Parry 1046955
 * @file Movable.h
 */
#ifndef MOVABLE_H
#define MOVABLE_H

class Movable {
public:

/**
 * @brief Constructor.
 */

	Movable();
	
	virtual ~Movable(){};
	/**
 * @brief Virtual function to allow a derived class object to move its position.
 * @param horizontal is the distance the derived object will move in the x plane.
 * @param vertical is the distance the derived class object will move in the y plane.
 */
	virtual void move(int horizontal, int vertical) = 0;
	

private:
	// going to be an interface
};

#endif