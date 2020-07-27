#include "CentipedeBlock.h"

centipedeBlock::centipedeBlock(int x, int y): _x(x), _y(y),_xPre(x),_yPre(y)  {
	
}

std::tuple<int,int> centipedeBlock::getPosit() {
	return {_x, _y};
}

std::tuple<int,int> centipedeBlock::getPrePosit() {
	return {_xPre, _yPre};
}

void centipedeBlock::setPosit(int x, int y) {
	_x = x;
	_y = y;
}

void centipedeBlock::setPrePosit(int x, int y) {
	_xPre = x;
	_yPre = y;
}

void centipedeBlock::decreaseNumberBlocks(){
	_noBlocks-=1;
}

void centipedeBlock::increaseNumberBlocks(){
	_noBlocks+=1;
}



centipedeBlock::~centipedeBlock(){
	}
	
	int centipedeBlock::_noBlocks = 0;