#include "EntityManager.h"
#include <stdlib.h> 
#include <time.h>    
#include <time.h>
#include <math.h>    
#include "DDTBomb.h"
#include <iostream>
void EntityManager::setup(int horz, int ver) {
	// setup all the centipedes and movables and alles
	_movables.push_back(std::make_shared<Player>(400, 500));
	_movables.push_back(std::make_shared<Centipede>(0, 0, 6, 0, -1, Direction::Right, Direction::NoDir));
//	_immovables.push_back(std::make_shared<Mushroom>(20, 0));
	centipedeBlock::_noBlocks = 7;
	generateMushrooms(horz, ver);
	
}

std::tuple<std::shared_ptr<std::vector<std::shared_ptr<Entity>>>,std::shared_ptr<std::vector<std::shared_ptr<Entity>>>> EntityManager::getEntities() {
	// check if co-ordinates haven't changed then only render
	return std::make_tuple(std::make_shared<std::vector<std::shared_ptr<Entity>>>(_movables), std::make_shared<std::vector<std::shared_ptr<Entity>>>(_immovables));
}

void EntityManager::update(int horz, int vert) {
	addDDTBomb();
	removeExplodedDDT();
	for(auto mov: _movables) {
		mov->setPrevPosition(mov->getPosition());
		mov->move(horz, vert);
	}
	auto i = 0;
	auto cxPos = 0;
	auto cyPos = 0;
	auto xPos = 0;
	auto yPos = 0;
	for(i;i<_movables.size();i++){
		if (_movables[i]->getType()==Type::Cent){
			
			for (auto k=0;k<_immovables.size();k++){
					std::vector<std::tuple<int,int>> obj1;
					std::vector<std::tuple<int,int>> obj2;
					auto cen = *(_movables[i]->getCentipede());
					auto head = cen.begin();
					obj1.push_back(head->getPrePosit());
					obj1.push_back(head->getPosit());
					std::get<0>(obj1[0])=std::get<0>(obj1[0])-2;
					std::get<1>(obj1[0])=std::get<1>(obj1[0]);
					std::get<0>(obj1[1])=std::get<0>(obj1[1]);
					std::get<1>(obj1[1])=std::get<1>(obj1[1]);
					
					obj2.push_back(_immovables[k]->getPosition());
					obj2.push_back(_immovables[k]->getPosition());
					
					if(_immovables[k]->getType()==Type::DDT) {
						std::get<0>(obj2[0])=std::get<0>(obj2[0])/16 -2;
						std::get<1>(obj2[0])=std::get<1>(obj2[0])/16;
						std::get<0>(obj2[1])=std::get<0>(obj2[1])/16;
						std::get<1>(obj2[1])=std::get<1>(obj2[1])/16;
					}
					
					if (_collision.checkCollision(obj1 ,obj2)){
						_movables[i]->setWallCollide(true);
						xPos = std::get<0>(head->getPosit());
						yPos = std::get<1>(head->getPosit());
					}
			}
		}
		if (_movables[i]->getType()==Type::Las){
			for (auto k=0;k<_immovables.size();k++){
					std::vector<std::tuple<int,int>> obj1;
					std::vector<std::tuple<int,int>> obj2;
					obj1.push_back(_immovables[k]->getPosition());
					obj1.push_back(_immovables[k]->getPosition());
					std::get<0>(obj1[0])=std::get<0>(obj1[0])*16-1;
					std::get<1>(obj1[0])=std::get<1>(obj1[0])*16;
					std::get<0>(obj1[1])=std::get<0>(obj1[1])*16+1;
					std::get<1>(obj1[1])=std::get<1>(obj1[1])*16;
					obj2.push_back(_movables[i]->getPrevPosition());
					obj2.push_back(_movables[i]->getPosition());
					
					if ((_collision.checkCollision(obj1 ,obj2)&&(_immovables[k]->getType()==Type::Mush))){
						_immovables[k]->decreaseHealth();
						if (_immovables[k]->getHealth()==0){
							_immovables.erase(_immovables.begin()+k);
							_entitiesShot.push_back(entityShot::Mush);
						}
						_movables.erase(_movables.begin()+i);
						goto endTimestep;
					}
					if ((_immovables[k]->getType()==Type::DDT)){
						std::get<0>(obj1[0])=std::get<0>(obj1[0])/16-10;
						std::get<1>(obj1[0])=std::get<1>(obj1[0])/16;
						std::get<0>(obj1[1])=std::get<0>(obj1[1])/16+10;
						std::get<1>(obj1[1])=std::get<1>(obj1[1])/16;
						
						if (_collision.checkCollision(obj1 ,obj2)){
							_movables.erase(_movables.begin()+i);
							DDTExplosion(k);
							goto endTimestep;

						}
					}
				}
			}
		
		for (auto j=i;j<_movables.size();j++){
			if (_movables[i]->getType()==Type::Cent){
				
				if (_movables[j]->getType()==Type::Las){
					std::vector<std::tuple<int,int>> obj1;
					std::vector<std::tuple<int,int>> obj2;
					auto cen = *(_movables[i]->getCentipede());
					auto head = cen.begin();
					
					obj1.push_back(head->getPrePosit());
					obj1.push_back(head->getPosit());
					obj2.push_back(_movables[j]->getPrevPosition());
					obj2.push_back(_movables[j]->getPosition());
					std::get<0>(obj1[0])=std::get<0>(obj1[0])*16-20;
					std::get<1>(obj1[0])=std::get<1>(obj1[0])*16-15;
					std::get<0>(obj1[1])=std::get<0>(obj1[1])*16+20;
					std::get<1>(obj1[1])=std::get<1>(obj1[1])*16+15;
					if (_collision.checkCollision(obj2 ,obj1)){
						cxPos = std::get<0>(head->getPosit());
						cyPos = std::get<1>(head->getPosit());
						centepedeDown(i,cxPos,cyPos);
						goto endTimestep;
					}

					for(auto iter = cen.begin()+1; iter != cen.end(); ++iter) {
						obj1.clear();
						obj1.push_back(iter->getPrePosit());
						obj1.push_back(iter->getPosit());
						std::get<0>(obj1[0])=std::get<0>(obj1[0])*16-20;
						std::get<1>(obj1[0])=std::get<1>(obj1[0])*16-15;
						std::get<0>(obj1[1])=std::get<0>(obj1[1])*16+20;
						std::get<1>(obj1[1])=std::get<1>(obj1[1])*16+15;
						if (_collision.checkCollision(obj2 ,obj1)){
							cxPos = std::get<0>(iter->getPosit());
							cyPos = std::get<1>(iter->getPosit());
							centepedeDown(i,cxPos,cyPos);
							goto endTimestep;
						}

					}
				}
				
			}
			
			if (_movables[i]->getType()==Type::Play){
				if (_movables[j]->getType()==Type::Cent){
					auto _blockSize=16;
					std::vector<std::tuple<int,int>> obj1;
					std::vector<std::tuple<int,int>> obj2;
					auto cen = *(_movables[j]->getCentipede());
					auto head = cen.begin();
					obj1.push_back(head->getPrePosit());
					obj1.push_back(head->getPosit());
					obj2.push_back(_movables[i]->getPrevPosition());
					obj2.push_back(_movables[i]->getPosition());
					
					std::get<0>(obj1[0])=std::get<0>(obj1[0])*16-20;
					std::get<1>(obj1[0])=std::get<1>(obj1[0])*16-15;
					std::get<0>(obj1[1])=std::get<0>(obj1[1])*16+20;
					std::get<1>(obj1[1])=std::get<1>(obj1[1])*16+15;
					
					if (_collision.checkCollision(obj2 ,obj1)){
						xPos = std::get<0>(head->getPosit());
						yPos = std::get<1>(head->getPosit());
						_movables[i]->decreaseHealth();
							_lose = true;
							resetGame();
							goto endTimestep;
					}

					for(auto iter = cen.begin()+1; iter != cen.end(); ++iter) {
						obj1.clear();
						obj1.push_back(iter->getPrePosit());
						obj1.push_back(iter->getPosit());
						
						
						if (_collision.checkCollision(obj2 ,obj1)){
							xPos = std::get<0>(iter->getPosit());
							yPos = std::get<1>(iter->getPosit());
							_movables[i]->decreaseHealth();
							_lose = true;
							resetGame();
							goto endTimestep;
						}
					}
				}
			}
			
		}
	}
	
	endTimestep:;
}

void EntityManager::handleEvent(Action ev) {
	auto moveX = 0;
	auto moveY = 0;
	_entitiesShot.clear();
	
	switch(ev) {
		case Action::Up:
			moveY=-16;
			break;
		case Action::Down:
			moveY=16;
			break;
		case Action::Left:
			moveX=-16;
			break;
		case Action::Right:
			moveX=16;
			break;
		case Action::DownRight:
			moveX=16;
			moveY=16;
			break;
		case Action::DownLeft:
			moveX=-16;
			moveY=16;
			break;
		case Action::UpLeft:
			moveX=-16;
			moveY=-16;
			break;
		case Action::UpRight:
			moveX=16;
			moveY=-16;
			break;
		case Action::Shoot:
			_movables.push_back(std::make_shared<Laser>(std::get<0>(_movables[0]->getPosition()), std::get<1>(_movables[0]->getPosition())-16));

			break;
		case Action::Close:
			
			break;
		case Action::None:
			break;
	}

	//	player always kept at first position of vector since never destroyed while game is running 
	
	_movables[0]->setMovements(moveX, moveY);
}

void EntityManager::generateMushrooms(int horz, int ver) {
	srand (time(NULL));
	auto count = 0;
	
	while (count < 10) {
		startLoop:
		auto row = rand()%780;
		auto col = rand()%470;
		for(auto m: _movables) {
			if(m->getType() == Type::Cent) {
				auto cen = *(m->getCentipede());
				for(auto iter = cen.begin();iter != cen.end(); ++iter) {
					if(row == std::get<0>(iter->getPosit()) && std::get<1>(iter->getPosit())) {
						goto startLoop;
					}
				}
			}
			else if(row == std::get<0>(m->getPosition()) && std::get<1>(m->getPosition())) {
				goto startLoop;
			}
		}
		_immovables.push_back(std::make_shared<Mushroom>(row/16, col/16));
		count ++;
	}
}

bool EntityManager::checkWin() {
	// check movables for centipedes
	auto seen = false;
	for(auto mov: _movables) {
		if(mov->getType() == Type::Cent) {
			seen = true;
		}
	}
	if(!seen) {
		_win = true;
	}
	return _win;
}

bool EntityManager::checkLoss() {
	if (_movables[0]->getHealth()>0){
	_lose=false;
	} 
	return _lose;
}

std::vector<entityShot> EntityManager:: getEntityshot(){
	return _entitiesShot;
}

void EntityManager::centepedeDown(int index,int cxPos,int cyPos){
	
		_entitiesShot.push_back(entityShot::Centi);
		centipedeBlock cent(1,1);
		cent.decreaseNumberBlocks();
		_immovables.push_back(std::make_shared<Mushroom>(cxPos, cyPos));
		auto response = _movables[index]->checkDestroy(cxPos, cyPos);
		if(response == -99) {
			_movables.erase(_movables.begin()+index);
			centipedeBlock cent(1,1);
			cent.decreaseNumberBlocks();
		}
		if(response == -1) {
			auto newCent = _movables[index]->destroySegment(0);
			if(newCent != nullptr) {
				_movables.push_back(newCent);
			}
			_movables.erase(_movables.begin()+index);
		}
		else if(response > 0) {
			auto newCent = _movables[index]->destroySegment(response);
			if(newCent != nullptr) {
				_movables.push_back(newCent);
			}
		}
}


void EntityManager::resetGame(){
		_entitiesShot.push_back(entityShot::Play);
	if(_movables[0]->getHealth()>0){ 
		for (auto move=0;move<_movables.size();move++){
			if (_movables[move]->getType()==Type::Cent){
				_movables.erase(_movables.begin()+move);
			}
		}
		_movables.push_back(std::make_shared<Centipede>(0, 0, centipedeBlock::_noBlocks, 0, -1, Direction::Right, Direction::NoDir));
		_lose=false;
		
	}
}

void EntityManager::DDTExplosion(int i){
	
	int blastRadius=_immovables[i]->getBlastRadius();
//	std::get<0>(obj1[0])=std::get<0>(obj1[0])*16-20;
//	std::get<1>(obj1[0])=std::get<1>(obj1[0])*16-15;
	auto posDDT=_immovables[i]->getPosition();
	
//	_immovables.erase(_immovables.begin()+i);
	_immovables[i]->setExploded();
	for (auto k=0;k<_immovables.size();k++){
		
		if ((abs(std::get<0>(posDDT)-std::get<0>(_immovables[k]->getPosition())*16)>blastRadius)||(abs(std::get<1>(posDDT)-std::get<1>(_immovables[k]->getPosition())*16)>blastRadius)){
		}
		else {
			auto distance=sqrt(pow(std::get<0>(posDDT)-std::get<0>(_immovables[k]->getPosition())*16,2)+pow(std::get<1>(posDDT)-std::get<1>(_immovables[k]->getPosition())*16,2));
			
			if ((distance<blastRadius)&&(distance!=0)){
				if(_immovables[k]->getType() == Type::DDT) {
					DDTExplosion(k);
				}
				_immovables.erase(_immovables.begin()+k);
				_entitiesShot.push_back(entityShot::DDT);
				
			}
		}
	}
	
	for (auto i=0;i<_movables.size();i++){
		if (_movables[i]->getType()==Type::Cent){
			auto cen = *(_movables[i]->getCentipede());
			auto head = cen.begin();
			auto obj1 =(head->getPosit());
			auto firstInRadius = -1;
			auto lastInRadius = -1;
			
			for(auto iter = cen.begin(); iter != cen.end(); ++iter) {
				if(sqrt(pow(std::get<0>(posDDT)-std::get<0>(iter->getPosit())*16,2)+pow(std::get<1>(posDDT)-std::get<1>(iter->getPosit())*16,2)) < blastRadius) {
					if(firstInRadius == -1) {
						firstInRadius = iter-cen.begin();
					}
					lastInRadius = iter-cen.begin();;
				}
			}
			
				if(firstInRadius != -1) {
					_entitiesShot.push_back(entityShot::DDT);
					auto newCent = _movables[i]->centBlast(firstInRadius, lastInRadius);
					
					if(newCent != nullptr) {
						_movables.push_back(newCent);
					}
					
					if(firstInRadius == 0) {
						_movables.erase(_movables.begin()+i);
					}
				}
			}
		}
//	}
}

void EntityManager::addDDTBomb(){
	
	std::random_device rd; 
    std::mt19937 eng(rd()); 
    std::uniform_int_distribution<> distr(0, 780); 
	auto randAllocation=rand()%100;
	if ((_DDTBombsCount < 4)&&(randAllocation==1)) {
		startLoop:
		auto row = rand()%780;
		auto col = rand()%470;

		for(auto m: _movables) {
			if(m->getType() == Type::Cent) {
				auto cen = *(m->getCentipede());
				for(auto iter = cen.begin();iter != cen.end(); ++iter) {
					if(row == std::get<0>(iter->getPosit()) && std::get<1>(iter->getPosit())) {
						goto startLoop;
					}
				}
			}
			else if(row == std::get<0>(m->getPosition()) && std::get<1>(m->getPosition())) {
				goto startLoop;
			}
		}
		_immovables.push_back(std::make_shared<DDTBomb>(row, col));
		_DDTBombsCount++;
	}
}

void EntityManager::removeExplodedDDT(){
	for (auto k=0;k<_immovables.size();k++){
		if ((_immovables[k]->getType()==Type::DDT)&&(_immovables[k]->hasExploded())&&(_immovables[k]->getTime()>9)){
		_immovables.erase(_immovables.begin()+k);
		_DDTBombsCount--;
//		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

}