#include "Score.h"

Score::Score()
{
}

Score::~Score()
{
	_score=0;
}

int Score::getScore() const{
	return _score;
}

void Score::updateScore(std::vector<entityShot> entities){
	for (auto x:entities){
		switch(x){
			case entityShot::Mush:
			_score+=10;
			break;
			case entityShot::Centi:
			_score+=25;
			break;
			case entityShot::Play:
			_score-=50;
			break;
			case entityShot::DDT:
			_score+=5;
			break;
		}
	}
}
