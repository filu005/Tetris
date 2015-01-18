#pragma once
#include <memory>
#include <vector>

#include "Tetromino.hpp"
#include "Painter.hpp"
#include "Board.hpp"
#include "AI.hpp"

#include <GL/glew.h>

class Game
{
public:
	enum Direction { UP, DOWN, LEFT, RIGHT };
	Game(int widthInBlocks, int heightInBlocks, GLfloat blockSize);

	void tick();
	void paint();
	void keyEvent(Direction);
	void fillTetrominoPool();
	Tetromino randTetrominoFromPool();
	void restart();

	void switchAIState() { _ai.flipState(); }

	double interval;

private:
	int _points;
	Painter _painter;
	std::shared_ptr<Board> _board;
	std::vector<Tetromino> _tetrominos;
	std::vector<Tetromino> _tetrominoPool;
	AI _ai;

};
