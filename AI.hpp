#pragma once
#include <utility>
#include <vector>

#include "Tetromino.hpp"
#include "Board.hpp"

//class Board;

class AI
{
public:
	enum State { STOP = 0, START = 1 };
	AI();

	std::pair<Tetromino, double> itsShowtime(Board& b, std::vector<Tetromino> tetrominos, unsigned int currentTetrominoIdx);
	void flipState() { _isRunning = (_isRunning == State::STOP) ? State::START : State::STOP; }
	bool isRunning() const { return (_isRunning == State::START); }

private:
	const double heightWeight = -0.66569;
	const double linesWeight = 0.99275;
	const double holesWeight = -0.46544;
	const double bumpinessWeight = -0.24077;

	State _isRunning;
};
