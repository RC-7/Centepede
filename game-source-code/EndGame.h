/**
 * @class EndGame
 * @brief The EndGame class encapsulates the information pertaining to the EndGame screen setup.
 * @author  Rashaad Cassim 1099797 and Jason Parry 104695
 * @file EndGame.h
 */

#ifndef ENDGAME_H
#define ENDGAME_H
#include <SFML/Graphics.hpp>

class EndGame {
public:
	/**
	 * @brief Constructor for a EndGame object.
	 * @param width is the width of the EndGame screen.
	 * @param height is the height of the EndGame screen.
	 */
	EndGame(int width, int height);
	
	/**
	 * @brief Returns the font used by the EndGame object.
	 */
	std::string getFont();
	
/**
 * @brief Rturns the title of the EndGame.
 */
	std::string getText();
	
/**
 * @brief Sets the text to be displayed in the EndGame screen based on the result of the game.
 * @param win is a boolian argument which is true when the Player has won.
 */

	void chooseText(bool win);
	

private:
	std::string _fontFile = "resources/Starjedi.ttf";
	std::string _text;
	int _width;
	int _height;
};

#endif