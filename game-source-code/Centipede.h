/**
 * @class Centipede
 * @brief The Centepede class encapsulates an enire Centipede which comprises of a train of cetipideBlock objects.
 * @author Rashaad Cassim 1099797 and Jason Parry 1046955
 * @file Centipede.h
 * 
 */
#ifndef CENTIPEDE_H
#define CENTIPEDE_H

#include <vector>
#include <memory>
#include <tuple>

#include "Direction.h"
#include "Entity.h"
#include "Movable.h"
#include "CentipedeBlock.h"

class Centipede: public Entity, public Movable {
public:

/**
 * @brief Default Constructor.
 */

	Centipede();
	
/**
 * @brief Constructor which creates a Centipede oject over a specified region.
 * @param startX the starting x Position at which to construct the Centipede.
 * @param startY the starting y Position at which to construct the Centipede.
 * @param endX the ending x Position at which to construct the Centipede.
 * @param endY the ending y Position at which to construct the Centipede.
 * @param bendX
 * @param dir the Direction that the Centipede is traveling.
 * @param prevDir the position of the Centipede at the previous timestep.
 * \see Direction
 */
	
	
	Centipede(int startX, int startY, int endX, int endY, int bendX, Direction dir, Direction prevDir);

/**
 * @brief Sets the Direction of the Centipede.
 * \see Direction
 */

	void setDirection(Direction dir);
	
/**
 * @brief Sets the Direction of the Centipede for the previous time-step.
 * \see Direction
 */
	void setPrevDirection(Direction dir);
	
/**
 * @brief Returns the position of the head of the Centipede.
 */

	std::tuple<int,int> getPos();
	
	
	
/**
 * @brief Returns the direction of the Centipede.
 */
	
	Direction getDirection() override;
	
/**
 * @brief Destroys a segment on the Centepede train and returns a shared pointer to the new Centipede.
 * @param posit is the index of the block on the Centipede train that is to be deleted.
 * \see CentipedeBlock
 */
	
	
	std::shared_ptr<Centipede> destroySegment(int posit) override;
	
	

/**
 * @brief Destroys a section of the Centipede segments hit by a DDTBomb explosion and returns the new Centipede created
 * @param firstIn is the index of the first Centipede segment hit by the DDTBomb
 * @param lastIn is the index of the last Centipede segment hit by the DDTBomb
 */

	std::shared_ptr<Centipede> centBlast(int firstIn, int lastIn) override;
	
/**
 * @brief Returns a pointer to a vector of centipedeBlock objects that the Centipede comprises of.
 */
	
	std::shared_ptr<std::vector<centipedeBlock>> getCentipede() override;
	int getHealth() override {}
	void decreaseHealth() override {}
	
	void setMovements(int x, int y) override {}
	int getBlastRadius() override{}
	
	
/**
 * @brief Moves the Centipede train for the current timestep.
 * @param horizontal is the horizontal dimention of the Display.
 * @param vertical is the vertical dimention of the Display.
 */
	
	void move(int horizontal, int vertical) override;
	
	
/**
 * @brief Dermines which destroy action should be implimented once a Centipede at a position is hit by a Laser by returning a responce code indicating the action which should be taken.
 * @param x is the x position of the Centipede segment hit.
 * @param y is the y position of the Centipede segment hit.
 */

	int checkDestroy(int x, int y) override;
	
/**
 * @brief Sets the wall colision status of the Centipede when it has colided with a wall.
 * @param coll is the status of the wall collision, i.e. it is true when the Centipede has colided with a wall.
 */
	
	void setWallCollide(bool coll) override;
	
private:
	int _moveStep = 16;
	
	std::vector<centipedeBlock> _centipede;
	Direction _dir;
	Direction _prevDir;
	
	bool _collision = false;
	bool _wallCollide = false;
	
	// used for when centipede reaches bottom of screen
	bool _bottom = false;
};

#endif