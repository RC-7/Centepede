/*!
 * \class Player 
 * @brief The class encapsulating the functionality of a Player within the Centepede Wars game environment.
 * \author Rashaad Cassim 1099797 and Jason Parry 1046955
 * \file Player.h
 */
#ifndef PLAYER_H
#define PLAYER_H
#include <tuple>
#include <SFML/Graphics.hpp>
#include "Entity.h"
   /** 
     * An enum class to define player movements and user inputs.
     * This allows the user inputs to be recorded by the EventManager.
     */
enum class Action{Up,/*!< Move Up */
 Down, /*!< Move Down */
 Left,/*!< Move Left */
 Right, /*!< Move Right */
 UpRight,/*!< Move Diagonally Up and Right */
 DownRight,/*!< Move Diagonally Down and Right */
 UpLeft,/*!< Move Diagonally Up and Left */
 DownLeft, /*!< Move Diagonally Down and Left */
 Shoot,/*!< Shoot a Laser */
 None,/*!< Default value */
 Close/*!< Close the Display */};

class Player: public Entity, protected Movable{
public:
/**
 * @brief Default constructor.
 */
	Player();
/**
 * @brief Constructor of a Player object initialising the Player's position.
 * @param x is the initial x position of the Player.
 * @param y iis the initial y position of the Player.
 */
	
	Player(int x, int y);
/**
 * @brief Sets the distance that the Player object will move in the time-step.
 * @param x is the movement in the x plane.
 * @param y is the movement in the y plane.
 * \see Action
 */
	
	void setMovements(int x, int y);
/**
 * @brief Moves the Player object, using the movement set for the current timestep. This is done within the area designated for the player to occupy.
 * @param horizontal is the horizontal dimension of the Display.
 * @param vertical is the vertical dimension of the Display.
 */
	void move(int horizontal, int vertical) override;
	
/**
 * @brief Decreases the Player objects health.
 */
	
	void decreaseHealth();
	
/**
 * @brief Returns the Player objects current health.
 */
	int getHealth() override;
	
/**
 * @brief Returns the current position of Player object.
 */
	std::tuple<int,int> getPosition();
	
	~Player();
private:
	int _moveX;
	int _moveY;
	int _health=3;
	int _moveStep = 25;

};

#endif // PLAYER_H
