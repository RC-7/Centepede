/**
 * @class centipedeBlock
 * @brief The centipedeBlock class encapsulates an individual segment on a Centipede train
 * @author Rashaad Cassim 1099797 and Jason Parry 1046955
 * @date 07/10/2018
 * @file CentipedeBlock.h

 */

#ifndef CENTIPEDEBLOCK_H
#define CENTIPEDEBLOCK_H

#include <tuple>

class centipedeBlock {
public: 
	static int _noBlocks; //!< Stores the number of centipedeBlock objects that exist.
         //!< 
	
/**
 * @brief Constructor for a centipedeBlock object at a position.
 * @param x is the centipeBlock object's position in the x plane.
 * @param y is the centipeBlock object's position in the y plane.
 */
	
	centipedeBlock(int x, int y);
	
/**
 * @brief Returns the position of a centipedeBlock object.
 */
	
	std::tuple<int,int> getPosit();
	
/**
 * @brief Sets the position of a centipedeBlock object.
 * @param x
 * @param y
 */
	
	void setPosit(int x, int y);
	
/**
 * @brief Returns the position of a centipedeBlock object during the previous time-step.
 */
	
	std::tuple<int,int> getPrePosit() ;
	
/**
 * @brief Sets the position of a centipedeBlock object during the previous time-step.
 * @param x
 * @param y
 */
	void setPrePosit(int x, int y);
	
/**
 * @brief Decrease the number of centipedeBlock objects that exist.
 */
	
	void decreaseNumberBlocks();
	
/**
 * @brief Increase the number of centipedeBlock objects that exist.
 */
	void increaseNumberBlocks();
	~centipedeBlock();
private:
	int _x;
	int _y;
	int _xPre;
	int _yPre;
	
	
};

#endif