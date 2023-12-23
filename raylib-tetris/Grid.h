#pragma once
#include <vector>
#include <raylib.h>

class Grid
{
public:
	Grid();
	void initialize();
	void draw();
	void print();
	bool isCellOutside(int row, int col);
	bool isCellEmpty(int row, int col);
	int clearFullRows();
	int grid[20][10];
private:
	bool isRowFull(int row);
	void clearRow(int row);
	void moveRowDown(int row, int numRows);
	int numRows, numCols;
	int cellSize;
	std::vector<Color> colors;
};

