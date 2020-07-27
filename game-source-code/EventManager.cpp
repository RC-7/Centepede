#include "EventManager.h"

EventManager::EventManager()
{
}

// TODO: add capability to shoot and move
Action EventManager::handleInputs(){
	auto moveDirection=Action::None;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) ){
		moveDirection= Action::DownRight;
	}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) ){
		moveDirection= Action::DownLeft;
	}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) ){
		moveDirection= Action::UpLeft;
	}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) ){
		moveDirection= Action::UpRight;
	}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ){
		moveDirection= Action::Up;
	} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
		moveDirection= Action::Down;
	} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ){
		moveDirection= Action::Left;
	} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ){
		moveDirection= Action::Right;
	} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) ){ 
		moveDirection= Action::Shoot;
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
		moveDirection=Action::Close;
	}
	return moveDirection;
}

EventManager::~EventManager()
{
}

