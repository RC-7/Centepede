/**
 * @class SplashScreen
 * @brief The SplashScreen class encapsulates the information pertaining to the SplashScreen setup.
 * @author Rashaad Cassim 1099797 and Jason Parry 1046955
 * @file EntityManager.h
 */
#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H
#include <SFML/Graphics.hpp>

class SplashScreen {
public:
//	SplashScreen();

	/**
	 * @brief Constructor for a SplashScreen object.
	 * @param width is the width of the SplashScreen.
	 * @param height is the height of the SplashScreen.
	 */
	SplashScreen(int width, int height);
	/**
	 * @brief Returns the font used by the SplashScreen object.
	 */
	std::string getFont();
	/**
	 * @brief Returns the text to be displayed in the SplashScreen.
	 */
	std::string getText();
/**
 * @brief Rturns the title of the SplashScreen.
 */

	std::string getTitle();
	
//	~SplashScreen();
private:
	std::string _fontFile = "resources/Starjedi.ttf";
	std::string _title;
	std::string _text;
	int _width;
	int _height;
};

#endif