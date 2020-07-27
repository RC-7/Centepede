#include "SplashScreen.h"

SplashScreen::SplashScreen(int width, int height) : _width(width), _height(height) {
	_title = "\t\t\tCentipede Wars ";
	_text = "\n\n The arrow keys move the spaceship \n\n The left control button shoots \n\n Don't let the centipede hit you \n\n Eliminate all centipede segments to win! \n\n Mushrooms make the centipede change direction \n\n Shoot DDT bombs to destroy surrounding objects \n\n Score by shooting the centipede, mushrooms and DDTs\n\n Press left Ctrl to play and Esc to exit";
}

std::string SplashScreen::getFont() {
	return _fontFile;
}

std::string SplashScreen::getText() {
	return _text;
}

std::string SplashScreen::getTitle() {
	return _title;
}