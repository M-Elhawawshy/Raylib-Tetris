#include "Game.h"
#include <random>
#include <iostream>

Game::Game() {
	grid = Grid();
	blocks = getAllBlocks();
	currentBlock = getRandomBlock();
	nextBlock = getRandomBlock();
	gameOver = false;
	score = 0;
	InitAudioDevice();
	music = LoadMusicStream("Sounds/music.mp3");
	PlayMusicStream(music);
	rotateSound = LoadSound("Sounds/rotate.mp3");
	clearSound = LoadSound("Sounds/clear.mp3");
}

Game::~Game() {
	UnloadSound(rotateSound);
	UnloadSound(clearSound);
	UnloadMusicStream(music);
	CloseAudioDevice();
}

Block Game::getRandomBlock() {
	if (blocks.empty()) {
		blocks = getAllBlocks();
	}
	int randomIndex = rand() % blocks.size();
	Block block = blocks[randomIndex];
	blocks.erase(blocks.begin() + randomIndex);

	return block;
}

void Game::draw() {
	grid.draw();
	currentBlock.draw(11, 11);
	switch (nextBlock.id)
	{
	case 3:
		nextBlock.draw(255, 290);
		break;
	case 4:
		nextBlock.draw(255, 280);
		break;
	default:
		nextBlock.draw(270, 270);
		break;
	}
}


std::vector<Block> Game::getAllBlocks() {
	return { IBlock(), JBlock() , LBlock() , OBlock(), SBlock(), TBlock(), ZBlock() };
}


void Game::handleInput() {
	auto key = GetKeyPressed();

	if (gameOver && IsKeyPressed(KEY_ENTER)) {
		resetGame();
	}

	switch (key)
	{
	case KEY_LEFT:
		moveBlockLeft();
		break;
	case KEY_RIGHT:
		moveBlockRight();
		break;
	case KEY_DOWN:
		if(!gameOver)
			score += 1;
		moveBlockDown();
		break;

	case KEY_E:
		rotateBlockClockwise();
		break;
	case KEY_Q:
		rotateBlockCounterClockwise();
		break;
	default:
		break;
	}
}


void Game::moveBlockLeft() {
	if (gameOver)
		return;

	currentBlock.move(0, -1);
	if (isBlockOutside() || !blockFits()) {
		currentBlock.move(0, 1);
	}

}


void Game::moveBlockRight() {
	if (gameOver)
		return;

	currentBlock.move(0, 1);
	if (isBlockOutside() || !blockFits()) {
		currentBlock.move(0, -1);
	}

}

void Game::moveBlockDown() {
	if (gameOver)
		return;

	currentBlock.move(1, 0);
	if (isBlockOutside() || !blockFits()){
		currentBlock.move(-1, 0);
		lockBlock();
	}

}

bool Game::isBlockOutside()
{
	auto positions = currentBlock.getCellPositions();
	
	for (const auto& pos : positions) {
		if (grid.isCellOutside(pos.row, pos.column)) {
			return true;
		}
	}

	return false;
}

void Game::rotateBlockClockwise()
{
	if (gameOver)
		return;
	PlaySound(rotateSound);
	currentBlock.rotateClockwise();
	if (isBlockOutside() || !blockFits()) {
		rotateBlockCounterClockwise();
	}
}

void Game::rotateBlockCounterClockwise()
{
	if (gameOver)
		return;

	PlaySound(rotateSound);
	currentBlock.rotateCounterClockwise();
	if (isBlockOutside() || !blockFits()) {
		rotateBlockClockwise();
	}
}

void Game::lockBlock()
{
	for (auto& i : currentBlock.getCellPositions()) {
		grid.grid[i.row][i.column] = currentBlock.id;
	}

	currentBlock = nextBlock;
	if (!blockFits()) {
		gameOver = true;
	}
	nextBlock = getRandomBlock();
	auto linesCleared = grid.clearFullRows();
	if (linesCleared > 0) {
		PlaySound(clearSound);
		updateScore(linesCleared, 0);
	}

}

bool Game::blockFits()
{
	for (const auto& pos : currentBlock.getCellPositions()) {
		if (!grid.isCellEmpty(pos.row, pos.column)) {
			return false;
		}
	}

	return true;
}

void Game::resetGame()
{
	grid.initialize();
	blocks = getAllBlocks();
	currentBlock = getRandomBlock();
	nextBlock = getRandomBlock();
	gameOver = false; 
	score = 0;
}

void Game::updateScore(int linesCleared, int moveDownPoints)
{
	switch (linesCleared)
	{
	case 1:
		score += 100;
		break;

	case 2:
		score += 300;
		break;

	case 3:
		score += 500;
		break;

	default:
		break;
	}
}