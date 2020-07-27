/**
 * @class Game
 * @brief The Game class encapsulates the "game engine".
 * @author Rashaad Cassim 1099797 and Jason Parry 104695
 * @file Game.h
 */


#ifndef GAME_H
#define GAME_H

#include "SplashScreen.h"
#include "Display.h"
#include "EventManager.h"
#include "EntityManager.h"
#include "Window.h"
#include "Entity.h"
#include "DataManager.h"
#include "EndGame.h"
#include "Score.h"
#include <string>
#include <memory>

// TODO: maybe change timing to chrono so that it is not dependent on SFML although we already have SFML included so makes sense to use it
#include <SFML/Audio.hpp>
#include <SFML/System/Clock.hpp>

class Game {
public:

/**
 * @brief Constructor for the Game object
 * @param width is the width of the Game.
 * @param height is the height of the Game.
 * @param blockSize is the Game objects' block-size.
 * @param title is the title of the Game object
 */
 

	Game(int width, int height, int blockSize, std::string title);

/**
 * @brief Setup for relavent parameters required for the game.
 */

	void setup();
	
/**
 * @brief Displays the SplashScreen Display.
 */
	
	void splash();
	
/**
 * @brief Calls all necessary object members and functions of Game to play Centipede Wars.
 */

	void play();

	
private:
	// member variables
	
	// helper functions
	
/**
 * @brief Restarts the clock.
 */
	
	void resetClock();
	
/**
 * @brief Updates all Entity objects in the Game and querries if the Player has won or lost during the last timestep.
 */

	void update();
	
/**
 * @brief Renders the Entity objects in the Game at their new positions.
 */

	void renderAll();

	// instantiated classes
	SplashScreen _splash;
	EndGame _endGame;
	EventManager _eventMan;
	
	Display _disp;
	EntityManager _entityMan;
	Window _window;
	std::shared_ptr<Score> _score{new Score{}};
	std::shared_ptr<DataManager> _dataManager{new DataManager{}};
	
//	Score _score;
	
	// TODO: check resizing issues
	bool _end = false;
	int _width = 800;
	int _height = 600;
	int _blockSize;
	float _timestep = 0.03f;
	sf::Clock _clock;
	float _timer;
};

#endif