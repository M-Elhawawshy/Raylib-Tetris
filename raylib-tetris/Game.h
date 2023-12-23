#pragma once
#include "Grid.h"
#include "Blocks.h"
class Game
{
public:
	Game();
	~Game();
	Block getRandomBlock();
	void draw();
	std::vector<Block> getAllBlocks();
	void handleInput();
	void moveBlockLeft();
	void moveBlockRight();
	void moveBlockDown();
	bool isBlockOutside();
	void rotateBlockClockwise();
	void rotateBlockCounterClockwise();
	void lockBlock();
	bool blockFits();
	Grid grid;
	bool gameOver;
	int score;
	Music music;
private:
	void resetGame();
	void updateScore(int linesCleared, int moveDownPoints);
	std::vector<Block> blocks;
	Block currentBlock;
	Block nextBlock;
	Sound rotateSound;
	Sound clearSound;
};

