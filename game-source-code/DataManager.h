/**
 * @class DataManager
 * @brief The DataManager class encapsulates the data layer of the Centipede Wars Game.
 * @author Rashaad Cassim 1099797 and Jason Parry 1046955
 * @file DataManager.h
 */
#ifndef DATAMANAGER_H
#define DATAMANAGER_H
#include <string>
#include <fstream>
#include <vector>
#include <tuple>
class DataManager
{
public:
/**
 * @brief Default constructor.
 */
	DataManager();
/**
 * @brief Default Destructor.
 */
	~DataManager();
/**
 * @brief Updates the high scores if the user's score is in the top five recorded scores.
 * @param score is the users score following winning a game.
 * @param name is the users name entered.
 */
	void updateHighScores(int score,std::string name);
	
/**
 * @brief Returns the recorded top scores and the names of the users that achieved them.
 */
	std::tuple<std::vector <std::string> ,std::vector <int>> getScores();

/**
 * @brief Updates a text file with the top five scores.
 */
	void updateFile();
	
private:
	std::string _scoreFile{"resources/HighScores.txt"};
	std::vector <std::string> _names;
	std::vector <int> _scores;
	

};

#endif // DATAMANAGER_H
