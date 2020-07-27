/**
 * @class EventManager
 * @brief The EventManager class is a wrapper around SFML input handling functionality.
 * @author Rashaad Cassim 1099797 and Jason Parry 1046955
 * @file EventManager.h
 */

#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H
#include <SFML/Window.hpp>
#include "Player.h"

class EventManager
{
public:
/**
 * @brief Default constructor.
 */

	EventManager();
/**
 * @brief Records the user input and returns a value of the enum class Action.
 * \see Action
 */
	Action handleInputs();
/**
 * @brief Default Destructor.
 */
	~EventManager();

};

#endif // EVENTMANAGER_H
