#pragma once
#include "PainterSquare.hpp"

class Painter;

class Board
{
public:
	Board(int widthInBlocks, int heightInBlocks);
	Board(const Board& b);
	~Board();

	void paint(Painter& p) const;
	bool collide(const Tetromino& t) const;
	bool canMoveDown(Tetromino t) const;
	bool canMoveLeft(Tetromino t) const;
	bool canMoveRight(Tetromino t) const;
	int removeLines();
	void merge(const Tetromino& t);

	// Heurystyki
	int aggregateHeight() const;
	int completeLines() const;
	int holes() const;
	int bumpiness() const;

	int getColHeight(int col) const;

	int getWidth() const { return _widthInBlocks; }
	int getHeight() const { return _heightInBlocks; }

	bool** board;

private:
	const int _widthInBlocks;
	const int _heightInBlocks;
};
