#include "Mushroom.h"
#include "Mushroom.h"

Mushroom::Mushroom(int x, int y): Entity(Type::Mush, x, y)
{
}

Mushroom::~Mushroom()
{
}

int Mushroom::getHealth() {
	return _health;
}

void Mushroom::decreaseHealth(){
	_health-=1;
}

bool Mushroom::hasHealth(){
	bool hasHealth=true;
	if(_health==0)
		hasHealth= false;
	return hasHealth;
}



