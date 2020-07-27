#include "Player.h"

Player::Player() {
	
}

Player::Player(int x, int y): Entity(Type::Play, x, y)
{
}


void Player::setMovements(int x, int y) {
	_moveX = x;
	_moveY = y;
}

void Player::move(int horizontal, int vertical) {
	auto p = Entity::getPosition();
	auto newX = std::get<0>(p)+_moveX;
	auto newY = std::get<1>(p)+_moveY;
	
	if(newX > horizontal - _moveStep) {
		newX = horizontal - _moveStep;
	}
	if(newX < 5) {
		newX = 5;
	}
	if(newY > vertical - 2*_moveStep) {
		newY = vertical - 2*_moveStep;
	}
	if(newY <= 0.8*vertical) {
		newY = 0.8*vertical;
	}
 
	Entity::setPosition(newX, newY);
	_moveX = 0;
	_moveY = 0;
}

void Player::decreaseHealth(){
	_health-=1;
}

int Player::getHealth(){
	return _health;
}


Player::~Player()
{
}

