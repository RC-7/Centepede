/**
 * @class Entity
 * @brief Entity is a template class upon which game Entities are built.
 * @author Rashaad Cassim 1099797 and Jason Parry 1046955
 * @file Entity.h
 */
#ifndef ENTITY_H
#define ENTITY_H

#include "Movable.h"
#include "CentipedeBlock.h"
#include "Direction.h"
//#include "Centipede.h"
#include <tuple>
#include <memory>
#include <vector>

class Centipede;
   /** 
     * An enum class to define the type of Entity.
     */
enum class Type{Cent,/*!< A Centipede Entity */
 Play,/*!< A Player Entity */
 Mush,/*!< A Mushroom Entity */
 Las,/*!< A Laser Entity */
 DDT, /*!< A DDTBomb Entity */
 NoType/*!< Default value */ };


class Entity {
public: 

/**
 * @brief Default Constructor.
 */

	Entity();
	
/**
 * @brief Constructor for an Entity of a specific Type at a position.
 * @param type is the Type of Entity.
 * @param x is the position in the x plane of the Entity.
 * @param y is the position in the y plane of the Entity.
 * \see Type
 */
	
	Entity(Type type, int x, int y);
/**
 * @brief Sets the Type of an Entity
 * \see Type
 */
	void setType(Type type);

/**
 * @brief Returns the Type of an Entity.
 * \see Type
 */

	Type getType();
	
/**
 * @brief Returns the position of an Entity.
 */
	
	std::tuple<int,int> getPosition();
	
/**
 * @brief Returns the position during the previous time-step of an Entity.
 */
	std::tuple<int,int> getPrevPosition();
	
/**
 * @brief Sets the previous position of an Entity.
 */
	
	void setPrevPosition(std::tuple<int,int>);
	
/**
 * @brief Sets the current position of an Entity.
 */
	void setPosition(int x, int y);
	virtual std::shared_ptr<std::vector<centipedeBlock>> getCentipede() {return nullptr;};
	virtual std::shared_ptr<Centipede> centBlast(int firstIn, int lastIn) {return nullptr;};
	virtual Direction getDirection() {return Direction::NoDir;};
	virtual void setMovements(int x, int y) {};
	virtual void move(int horizontal, int vertical) {};
	virtual int checkDestroy(int x, int y) {return -1;};
	virtual std::shared_ptr<Centipede> destroySegment(int posit) {return nullptr;};
	virtual int getHealth() {return -1;};
	virtual void decreaseHealth() {};
	virtual void setWallCollide(bool coll) {};
	virtual int getBlastRadius(){return -1;};
	virtual void setExploded(){};
	virtual bool hasExploded(){};
	virtual void incrimentTime(){};
	virtual int getTime(){return -1;};
	
	
	
//	~Entity();
	
private:
	// member variables
	Type _type;
	std::tuple<int, int> _pos;
	std::tuple<int, int> _prevPos;
	// helper functions
	
	
	// instantiated classes
};

#endif