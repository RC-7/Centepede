#include "Entity.h"

Entity::Entity() {
	
}

Entity::Entity(Type type, int x, int y): _type(type), _pos(x,y), _prevPos(x,y)
{
}

void Entity::setType(Type type) {
	_type = type;
}

Type Entity::getType() {
	return _type;
}

std::tuple<int,int> Entity::getPosition() {
	return _pos;
}
std::tuple<int,int> Entity::getPrevPosition() {
	return _prevPos;
}

void Entity::setPrevPosition(std::tuple<int, int> prev) {
	_prevPos = prev;
}

void Entity::setPosition(int x, int y) {
	std::get<0>(_pos) = x;
	std::get<1>(_pos) = y;
}

std::shared_ptr<std::vector<centipedeBlock>> getCentipede() {
	
}

Direction getDirection() {
	
}