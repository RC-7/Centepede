/**
 * @class Score
 * @brief The Score class encapsulates the functionality of a scoreboard in the Centipede Wars Game.
 * @author Rashaad Cassim 1099797 and Jason Parry 1046955
 * @file Score.h
 */
#ifndef SCORE_H
#define SCORE_H
#include "EventManager.h"
#include "entity.h"
   /** 
     * An enum class to define player movements and user inputs.
     * This allows the user inputs to be recorded by the EventManager.
     */
enum class entityShot{Mush,/*!< A mushroom has been destroyed */
Centi,/*!< A centipede segment has been destroyed */
Play,/*!< The player has been hit*/
DDT /*!< The DDT bomb has destroyed an Entity*/};

class Score
{
public:
/**
 * @brief Default constructor.
 */

	Score();
/**
 * @brief Returns the Player object's current score
 */
	
	int getScore()const;
	
/**
 * @brief Updates the Score based on what Entity was hit.
 * \see entityShot
 * @param entities is the entity shot defined by the enum class entityShot.
 */
	void updateScore(std::vector<entityShot> entities);
	

/**
 * @brief Destructor.
 */
	
	~Score();
	
private:
	int _score=0;
};

#endif // SCORE_H
