#include "DDTBomb.h"

DDTBomb::DDTBomb(int x, int y): Entity(Type::DDT, x, y)
{
	//try construct with refernce to what it will destroy
}



DDTBomb::~DDTBomb()
{
	
}

int DDTBomb::getBlastRadius(){
	return _blastRadius;
}

void DDTBomb::incrimentTime(){
	_time+=1;
}

int DDTBomb:: getTime(){
	return _time;
}

void DDTBomb::setExploded(){
	_exploded=true;
}

bool DDTBomb::hasExploded(){
	return _exploded;
}



