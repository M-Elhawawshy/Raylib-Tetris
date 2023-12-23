#include "Grid.h"
#include <iostream>

Grid::Grid()
{
	numRows = 20;
	numCols = 10;
	cellSize = 30;
	Grid::initialize();
	colors = { DARKGRAY, GREEN, RED, ORANGE, YELLOW, PURPLE, {21, 204, 209, 255}, BLUE };
}

void Grid::initialize()
{
	for (size_t i = 0; i < numRows; i++)
	{
		for (size_t j = 0; j < numCols; j++)
		{
			grid[i][j] = 0;
		}
	}
}

void Grid::draw()
{
	for (size_t i = 0; i < numRows; i++)
	{
		for (size_t j = 0; j < numCols; j++)
		{
			auto cellValue = grid[i][j];
			DrawRectangle(j * cellSize + 11, i * cellSize + 11, 29, 29, colors[cellValue]);
		}
	}
}


void Grid::print() {
	for (const auto& i : this->grid) {
		for (const auto& j : i) {
			std::cout << j << " ";
		}
		std::cout << "\n";
	}
}

bool Grid::isCellOutside(int row, int col)
{
	if (row >= 0 && row < numRows && col >= 0 && col < numCols)
		return false;

	return true;
}

bool Grid::isCellEmpty(int row, int col)
{
	if (grid[row][col] == 0)
		return true;

	return false;
}

int Grid::clearFullRows()
{
	int compeleted = 0;

	for (int row = numRows - 1; row >= 0; row--) {
		if (isRowFull(row)) {
			clearRow(row);
			compeleted++;
		}
		else if (compeleted > 0) {
			moveRowDown(row, compeleted);
		}
	}

	return compeleted;
}

bool Grid::isRowFull(int row)
{
	for (int i = 0; i < numCols; i++) {
		if (grid[row][i] == 0) {
			return false;
		}
	}

	return true;
}

void Grid::clearRow(int row)
{
	for (int i = 0; i < numCols; i++) {
		grid[row][i] = 0;
	}
}

void Grid::moveRowDown(int row, int numRows)
{
	for (int i = 0; i < numCols; i++) {
		grid[row + numRows][i] = grid[row][i];
		grid[row][i] = 0;
	}
}

