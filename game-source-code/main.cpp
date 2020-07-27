#include "Game.h"
#include <chrono>
#include <thread>
/*! \mainpage Code documentation for the Centepede Wars
 *
 * \section intro_sec Introduction
 *
 * This is the documentation page for the Centepede Wars game developed by 
 * Jason Parry and Rashaad Cassim. This game is based on the Atari game Centipede and 
 * has a Star Wars theme. It uses SFML as a base for it's GUI development.
 *
 * \section install_sec Class Diagram of system
 * \image html C:\ClassDiagram.PNG
 *
 * \section install_sec Acknowledgements
 *
 *
 *  */

int main(){
	// Program entry point.
	auto width = 800;
	auto height = 600;
	auto blockSize = 16;
	auto title = "Centipede Wars";
	Game game(width, height, blockSize, title);
	
	//TODO: move music?
	 sf::Music music;
	if (!music.openFromFile("resources/Crimson Drive.wav")){
		
	}
		music.setLoop(true);
		music.play();
	
	if (music.getStatus() == sf::Music::Playing){
		game.splash();
		game.setup();
		game.play();
	}
}