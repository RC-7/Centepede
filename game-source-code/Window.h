/**
 * @class Window
 * @brief The Window class encapsulates physical information about the Display such as it's dimentions.
 * @author Rashaad Cassim 1099797 and Jason Parry 104695
 * @file Window.h
 */
#ifndef WINDOW_H
#define WINDOW_H

#include <tuple>

class Window {
public: 
/**
 * @brief Constructor for a Window object.
 * @param wid is the width of the Window object.
 * @param hght is the height of the Window object.
 * @param bs is the block size of the Window object.
 */
	Window(int wid, int hght, int bs);
/**
 * @brief Returns the Window objects block size.
 */
	
	int getBlockSize();
	
/**
 * @brief Returns the width and height of the Window object.
 */
	
	std::tuple<int, int> getDimensions();
	
	//dont think ever used
	std::tuple<int, int> edgePlayerWindow(int newX, int newY);
	
private:
	// member variables
	int _width;
	int _height;
	int _blockSize;
	
	// helper functions
	
	
	// instantiated classes
};

#endif