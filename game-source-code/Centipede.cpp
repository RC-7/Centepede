#include "Centipede.h"
#include "Entity.h"
#include <memory>

Centipede::Centipede(): Entity() {
	
}

Centipede::Centipede(int startX, int startY, int endX, int endY, int bendX, Direction dir, Direction prevDir): Entity(Type::Cent, startX, startY), _dir(dir) {
	switch(dir) {
		case Direction::Right:
			if(startY == endY) {
				for(int i = endX; i >= startX; --i) {
					_centipede.push_back(centipedeBlock(i,startY));
				}
			}
			// can only happen after collided with left wall or mushroom and body is bent around
			else {
				for(int i = endX; i >= startX; --i) {
					if(i > bendX) {
						_centipede.push_back(centipedeBlock(i,startY));
					}
					else if(i < bendX) {
						_centipede.push_back(centipedeBlock(i,endY));
					}
					else {
						_centipede.push_back(centipedeBlock(i,startY));
						_centipede.push_back(centipedeBlock(i,endY));
					}
				}			
			break;
			
			case Direction::Left:
			if(startY == endY) {
				for(int i = startX; i <= endX; ++i) {
					_centipede.push_back(centipedeBlock(i,startY));
				}
			}
			// can only happen after collided with right wall or mushroom and body is bent around
			else {
				for(int i = startX; i <= endX; ++i) {
					if(i < bendX) {
						_centipede.push_back(centipedeBlock(i,startY));
					}
					else if(i > bendX) {
						_centipede.push_back(centipedeBlock(i,endY));
					}
					else {
						_centipede.push_back(centipedeBlock(i,startY));
						_centipede.push_back(centipedeBlock(i,endY));
					}
				}
			}
			
				break;
			
			// can only happen if head is shot while moving down
			case Direction::Down:
				_dir = prevDir;
				
				if(_dir == Direction::Right) {
					for(int i = endX; i >= startX; --i) {
						_centipede.push_back(centipedeBlock(i,startY));
					}
				}
				else {
					for(int i = startX; i <= endX; ++i) {
						_centipede.push_back(centipedeBlock(i,startY));
					}
				}
				
				break;
			
			// not currently possible
			case Direction::Up:
			if(startY == endY) {
				
			}
			else {
				
			}
			
				break;
				
			case Direction::NoDir:
				break;
			}
	}

}

void Centipede::setDirection(Direction dir) {
	_dir = dir;
}

Direction Centipede::getDirection() {
	return _dir;
}

std::tuple<int,int> Centipede::getPos() {
	return _centipede[0].getPosit();
}

std::shared_ptr<std::vector<centipedeBlock>> Centipede::getCentipede() {
	return std::make_shared<std::vector<centipedeBlock>>(_centipede);
}

void Centipede::setPrevDirection(Direction dir) {
	_prevDir = dir;
}

void Centipede::setWallCollide(bool coll) {
	_wallCollide = coll;
}

void Centipede::move(int horizontal, int vertical) {
	auto xPos = std::get<0>(_centipede[0].getPosit());
	auto yPos = std::get<1>(_centipede[0].getPosit());
	
	_centipede[0].setPrePosit(std::get<0>(_centipede[0].getPosit()),std::get<1>(_centipede[0].getPosit()));
	
	for (int i = _centipede.size() - 1; i > 0; --i) {
		_centipede[i].setPrePosit(std::get<0>(_centipede[i].getPosit()),std::get<1>(_centipede[i].getPosit()));
		_centipede[i].setPosit(std::get<0>(_centipede[i-1].getPosit()), std::get<1>(_centipede[i-1].getPosit()));
	}
	
	if((xPos*_moveStep) == horizontal-_moveStep || (xPos*_moveStep) == 0) {
		_wallCollide = true;
	}
	
	// if it hits bottom, must reverse
	if(_wallCollide) {
		if(((yPos*_moveStep) > vertical - (3*_moveStep) && !_bottom) || ((yPos*_moveStep) == 0 && _bottom)) {
			_bottom = !_bottom;
		}
	}
	
	// I'll refactor later to remove the arrow code
	if(_wallCollide && !_collision) {
		//later add in check for hit bottom to go back up
		
		if(!_bottom) {
			_centipede[0].setPosit(xPos, yPos+1);
			_prevDir = _dir;
			_dir = Direction::Down;
			_collision = true;
		}
		else {
			_centipede[0].setPosit(xPos, yPos-1);
			_prevDir = _dir;
			_dir = Direction::Up;
			_collision = true;
		}
	}
	else {
		switch(_dir) {
			case Direction::Up:
				if(_prevDir == Direction::Left) {
					_dir = Direction::Right;
					_centipede[0].setPosit(xPos+1, yPos);
				}
				else if(_prevDir == Direction::Right) {
					_dir = Direction::Left;
					_centipede[0].setPosit(xPos-1, yPos);
				}
				break;
			
			case Direction::Down:
				if(_prevDir == Direction::Left) {
					_dir = Direction::Right;
					_centipede[0].setPosit(xPos+1, yPos);
				}
				else if(_prevDir == Direction::Right) {
					_dir = Direction::Left;
					_centipede[0].setPosit(xPos-1, yPos);
				}
				break;
				
			case Direction::Left: 
				_centipede[0].setPosit(xPos-1, yPos);
				break;
				
			case Direction::Right: 
				_centipede[0].setPosit(xPos+1, yPos);
				break;
				
			case Direction::NoDir:
				break;
		}
		_wallCollide = false;
		_collision = false;
	}
}

// if collision detected in game, call this
int Centipede::checkDestroy(int x, int y) {
	if(_centipede.size() == 1) {
		return -99;
	}
	else {
		for(int i=0; i < _centipede.size(); ++i) {
			if(std::get<0>(_centipede[i].getPosit()) == x && std::get<1>(_centipede[i].getPosit()) == y) {
				if((i == 0)) {
					return -1;
				}
				else {
					if(i != _centipede.size()-1) {
						return i;
					}
					else {
						_centipede.pop_back();
						return 0;
					}
				}
			}
		}
	}
}

std::shared_ptr<Centipede> Centipede::destroySegment(int posit) {
	std::shared_ptr<Centipede> cent = nullptr;
	auto bendX = -1;
	auto positX = std::get<0>(_centipede[posit+1].getPosit());
	auto positY = std::get<1>(_centipede[posit+1].getPosit());
	auto tailX = std::get<0>(_centipede[_centipede.size()-1].getPosit());
	auto tailY = std::get<1>(_centipede[_centipede.size()-1].getPosit());
	
	if(positY != tailY) {
		for(auto i = posit+1; i != _centipede.size()-1; ++i) {
			if(std::get<1>(_centipede[i].getPosit()) != positY) {
				bendX = std::get<0>(_centipede[i].getPosit());
			}
		}
	}
	
	if(_dir == Direction::Right || _prevDir == Direction::Left) {
		cent = std::make_shared<Centipede>(tailX, tailY, positX, positY, bendX, _dir, _prevDir);
	}
	else if(_dir == Direction::Left || _prevDir == Direction::Right) {
		cent = std::make_shared<Centipede>(positX, positY, tailX, tailY, bendX, _dir, _prevDir);
	}
	
	if(posit != 0) {
		for(int i = _centipede.size()-1; i >= posit; --i) {
			_centipede.pop_back();
		}
	}
	
	return cent;
}

std::shared_ptr<Centipede> Centipede::centBlast(int firstIn, int lastIn) {
	std::shared_ptr<Centipede> cent = nullptr;
	auto lastX = std::get<0>(_centipede[lastIn+1].getPosit());
	auto lastY = std::get<1>(_centipede[lastIn+1].getPosit());
	auto tailX = std::get<0>(_centipede[_centipede.size()-1].getPosit());
	auto tailY = std::get<1>(_centipede[_centipede.size()-1].getPosit());
	auto bendX = -1;
	
	// head is included
	if(firstIn == 0 && lastIn == _centipede.size()-1) {
		return nullptr;
	}
	else if(firstIn == 0) {
		if(_dir == Direction::Right || _prevDir == Direction::Left) {
			cent = std::make_shared<Centipede>(tailX, tailY, lastX, lastY, bendX, _dir, _prevDir);
		}
		else if(_dir == Direction::Left || _prevDir == Direction::Right) {
			cent = std::make_shared<Centipede>(lastX, lastY, tailX, tailY, bendX, _dir, _prevDir);
		}
	}
	// head not included and tail not included
	else if(lastIn != _centipede.size()-1) {
		if(_dir == Direction::Right || _prevDir == Direction::Left) {
			cent = std::make_shared<Centipede>(tailX, tailY, lastX, lastY, bendX, _dir, _prevDir);
		}
		else if(_dir == Direction::Left || _prevDir == Direction::Right) {
			cent = std::make_shared<Centipede>(lastX, lastY, tailX, tailY, bendX, _dir, _prevDir);
		}
		
		for(auto i = _centipede.size()-1; i >= firstIn; --i) {
			_centipede.pop_back();
		}
	}
	// head not included and tail included
	else {
		for(auto i = _centipede.size()-1; i >= firstIn; --i) {
			_centipede.pop_back();
		}
	}
	
	// case where the centipede is turning, need to create two new centipedes 
	
	return cent;
}