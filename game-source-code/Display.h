/**
 * @class Display
 * @brief The Display class encapsulates visually rendering Entity objects on the screen and forms an adapter to the SFML framework.
 * @author Rashaad Cassim 1099797 and Jason Parry 1046955
 * @file Display.h
 */
#ifndef DISPLAY_H
#define DISPLAY_H



/////////////////////////////////////////////////////////////////////////////////////////////
///////////// for all the render fn's I havent added the argument parameters because 
///////////// I thaught them quite self explanatory, thaught I'd just add a see me....
//// not sure though. Agree?
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////



#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <memory>
#include "Entity.h"
#include "Player.h"
#include "Laser.h"
#include "Centipede.h"
#include "Mushroom.h"
#include "DDTBomb.h"
#include "SplashScreen.h"
#include "EventManager.h"
#include "DataManager.h"
#include "EndGame.h"
#include "Score.h"
#include <string>

class Display
{
public:
/**
 * @brief Default constructor.
 */

	Display();
	
/**
 * @brief Constructs a Display Window object with specific parameters.
 * @param wid is the width of the Display.
 * @param hght is the height of the Display.
 * @param blockSize is the Display objects' block-size.
 * @param title is the title of the Display object
 */
	
	Display(int wid, int hght, int blockSize, std::string title);

	
/**
 * @brief Provides the intitial setup for the display by rendering an empty window and loading all necessary textures.
 */
	
	void setup();

/**
 * @brief Clears the Display to a black screen.
 */

	
	void resetScreen();
	
/**
 * @brief Displays all drawn Entity objects on the Display.
 */
	
	void display();

/**
 * @brief Returns true if the Display window is open.
 */

	bool windowStatus();
	
/**
 * @brief Polls for a window close event.
 */
	
	bool checkEvent();
	
/**
 * @brief Returns true of the window close event occurs.
 */
	
	bool eventClosed();
	
/**
 * @brief Closes the Display.
 */
	
	void closeWindow();
	
/**
 * @brief Renders the Player object's score during the game.
 * @param score is the users score at the particular time-step.
 */
	
	void RenderScore(std::shared_ptr<Score> score);
	
/**
 * @brief Calls the appropriate render member function for an Entity.
 * @param ent is the Entity to be rendered on the Display.
 */

	void Render(std::shared_ptr<Entity> ent);
	
/**
 * @brief Renders the SplashScreen on the Display
 * \see SplashScreen
 */
	void RenderSplash(std::shared_ptr<SplashScreen> splash);
	
/**
 * @brief Renders the EndGame screen on the Display which allows the user to enter their name.
 * \see EndGame
 * \see Score
 */
	
	std::string RenderEndGame(std::shared_ptr<EndGame> endGame, std::shared_ptr<Score> score);
	
/**
 * @brief Renders a Centipede object on the display.
 * \see Centipede
 * \see CentipedeBlock
 */
	
	void RenderCentipede(std::shared_ptr<Entity> cent);
	
	
/**
 * @brief Renders a Laser object on the Display
 * \see Laser
 */

	void RenderLaser(std::shared_ptr<Entity> las);
	
/**
 * @brief Renders a Player object on the Display
 * \see Player
 */

	void RenderPlayer(std::shared_ptr<Entity> play);
	
/**
 * @brief Renders a Mushroom object on the display
 * \see Mushroom
 */

	void RenderMushroom(std::shared_ptr<Entity> mush);
/**
 * @brief Renders a DDTBomb object on the Display
 * \see DDTBomb
 */

	void RenderDDT(std::shared_ptr<Entity> ddt);
	
/**
 * @brief Renders the past high scores on the Display once the game has ended.
 * \see DataManager
 */

	void RenderHighScores(std::shared_ptr<DataManager> man);
	
/**
 * @brief Renders the Player object's healthbar on the Display during the game
 *\see Player
 */

	void RenderHealthBar(std::shared_ptr<Entity> play);

	
//TODO: load each character's texture in setup instead of everytime we render
private:
	int _width;
	int _height;
	int _blockSize;
	sf::RenderWindow _win; 
	sf::Event _event;
	
	//splash 
	sf::Font _splashFont;
	sf::Text _splashText;
	sf::Color _splashTextColour = sf::Color::Yellow;
	int _splashTitleSize = 40;
	int _splashTextSize = 22;
	
	//game screen
	sf::Texture _textureBCK;
	sf::Sprite _background;
	std::string _backFile = "resources/Flat Night 4 BG.png";
	
	//centipede
	sf::Texture _textureCentiiter;;
//	sf::Sprite _spriteCH;
	sf::Texture _textureCenti;
	
	sf::Sprite _spriteC;
	
	//player
	sf::Texture _texturePlay;
	sf::Sprite _spritePlay;
	sf::Texture textureHbar;
	
	//laser
	sf::Texture _textureLas;
//	sf::Sprite _laserSprite;
	
	//mushroom
	sf::Texture _textureMush1;
	sf::Texture _textureMush2;
	sf::Texture _textureMush3;
	
	//DDT
	sf::Texture _textureDDT;
	sf::Texture _textureExplosion;;
	
	// end game screen 
	sf::Font _endFont;
	sf::Text _endText;
	sf::Color _endTextColour = sf::Color::Yellow;
	int _endTextSize = 26;
	
	// helper functions

};

#endif // DISPLAY_H
