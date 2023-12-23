#include "Block.h"
#include <iostream>

Block::Block()
{
	cellSize = 30;
	rotationState = 0;
	colors = { DARKGRAY, GREEN, RED, ORANGE, YELLOW, PURPLE, {21, 204, 209, 255}, BLUE };
	rowOffset = 0;
	columnOffset = 0;
}

void Block::draw(int offsetX, int offsetY)
{
	std::vector<Position> tiles = getCellPositions();
	for (Position i : tiles) {
		DrawRectangle(i.column * cellSize + offsetX, i.row * cellSize + offsetY, cellSize - 1, cellSize - 1, colors[id]);
	}
}


void Block::move(int rows, int columns) {
	rowOffset += rows;
	columnOffset += columns;
}

void Block::rotateClockwise()
{
	rotationState = (rotationState + 1) % 4;
}

void Block::rotateCounterClockwise()
{
	rotationState--;
	if (rotationState == -1)
		rotationState = 3;
}


std::vector<Position> Block::getCellPositions() {
	std::vector<Position> pos;
	for (const auto& i : cells[rotationState]) {
		pos.push_back({ i.row + rowOffset, i.column + columnOffset });
	}

	return pos;
}