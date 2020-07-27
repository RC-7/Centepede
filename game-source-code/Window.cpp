#include "Window.h"

#include <tuple>

Window::Window(int wid, int hght, int bs) : _width(wid), _height(hght), _blockSize(bs) {
}

int Window::getBlockSize() {
	return _blockSize;
}

std::tuple<int, int> Window::getDimensions() {
	return {_width, _height};
}

std::tuple<int, int> Window::edgePlayerWindow(int newX, int newY) {
	if(newX > _width - _blockSize) {
		newX = _width - _blockSize;
	}
	if(newX < 10) {
		newX = 10;
	}
	if(newY > _height - _blockSize) {
		newY = _height-_blockSize;
	}
	if(newY <= 0.8*_height) {
		newY = 0.8*_height;
	}
	return std::tuple<int,int> {newX, newY};
}