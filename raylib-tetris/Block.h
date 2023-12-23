#pragma once
#include <vector>
#include <map>
#include "Position.h"
#include <raylib.h>

class Block
{
public:
	Block();
	int id;
	std::map<int, std::vector<Position>> cells;
	void draw(int offsetX, int offsetY);
	void move(int rows, int columns);
	void rotateClockwise();
	void rotateCounterClockwise();
	std::vector<Position> getCellPositions();
private:
	int cellSize;
	int rotationState;
	std::vector<Color> colors;
	int rowOffset;
	int columnOffset;
};

