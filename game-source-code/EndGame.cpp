#include "EndGame.h"

EndGame::EndGame(int width, int height) : _width(width), _height(height) {
	
}

std::string EndGame::getFont() {
	return _fontFile;
}

std::string EndGame::getText() {
	return _text;
}

void EndGame::chooseText(bool win) {
	if(win) {
		_text = "You Win";
	}
	else {
		_text = "You Lose";
	}
}