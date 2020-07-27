/**
 * @class EntityManager
* @brief The EntityManager class handles interactions between different Entity objects over the course of a Game.
 * @author Rashaad Cassim 1099797 and Jason Parry 1046955
 * @file EntityManager.h

 */
#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "Entity.h"
#include "Player.h"
#include "Collision.h"
#include "Centipede.h"
#include "CentipedeBlock.h"
#include "DDTBomb.h"
#include "Score.h"
#include "Laser.h"
#include "Mushroom.h"
#include <tuple>
#include <cmath>
#include <memory>
#include <vector>
#include <random>
#include <chrono>
#include <thread>

class EntityManager {
public: 
//	EntityManager();
	/**
	 * @brief Initialises the game screen with all necessary Entity objects.
	 * @param horz is the horizontal dimension of the game screen.
	 * @param ver is the vertical dimension of the game screen.
	 */
	void setup(int horz, int ver);
	
	/**
	 * @brief Updates the Game screens' Entity objects for the time-step.
	 * @param horz is the horizontal dimension of the game screen.
	 * @param ver is the vertical dimension of the game screen.
	 */
	void update(int horz, int ver);
	
	/**
	 * @brief Returns a shared pointer to a vector of all Movable Entity objects currently in the game.
	 */
	std::unique_ptr<std::vector<std::shared_ptr<Entity>>> getMovables();
	

		/**
		 * @brief Returns a shared pointer to a vector of all Immovable Entity objects currently in the game.
		 */
	std::unique_ptr<std::vector<std::shared_ptr<Entity>>> getImmovables();
	

	/**
	 * @brief Handles the interaction between the user input being recorded and its affect on the Game's Entity objects.
	 * @param ev is the user input that has occurred.
	 *\see Action
	 *\see EventManager
	 */
	void handleEvent(Action ev);
	
	/**
	 * @brief Evaluates if the player has eliminated all Centipede objects.
	 */
	bool checkWin();
	
	/**
	 *
	 * @brief Evaluates if the player has run out of lives.
	 */
	bool checkLoss();
	
	
	
/**
 * @brief Removes DDTBomb objects that have been shot after their explosion animation has been displayed for a sufficient number of timesteps.
 */

	void removeExplodedDDT();
	
	
	/**
	 * @brief Returns a vector of which Entity objects were destroyed during the time-step.
	 */
	std::vector<entityShot> getEntityshot();
	
	/**
	 *
	 * @brief Returns a tuple of shared pointers to a vector of movable and immovable Entity objects currently in the game.
	 */

	std::tuple<std::shared_ptr<std::vector<std::shared_ptr<Entity>>>,std::shared_ptr<std::vector<std::shared_ptr<Entity>>>> getEntities();

	
private:
	// member variables
	Collision _collision;
	std::vector<std::shared_ptr<Entity>> _movables;
	std::vector<std::shared_ptr<Entity>> _immovables;
	bool _win = false;
	bool _lose = false;
	
	bool _shot = false;
	std::vector<entityShot> _entitiesShot;
	
	// helper functions
	void updateCent(int h, int v);
	void updatePlayer(int h, int v);
	void updateLaser();
	void updateMushroom();
	void generateMushrooms(int horz, int ver);
	void centepedeDown(int index,int cxPos,int cyPos);
	void DDTExplosion(int i);
	void addDDTBomb();
	void resetGame();
	int _DDTBombsCount=0;
	// instantiated classes
};

#endif