#include "Laser.h"
#include "Player.h"

Laser::Laser() {
	
}

Laser::Laser(int x, int y): Entity(Type::Las, x, y) {

}



void Laser::move(int horizontal, int vertical){
	auto newX = std::get<0>(Entity::getPosition());
	auto newY = std::get<1>(Entity::getPosition());
	Entity::setPosition(newX, newY-_moveStep);
}


Laser::~Laser()
{
}

