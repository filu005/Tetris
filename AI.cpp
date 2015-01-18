#include "AI.hpp"

AI::AI(void) : _isRunning(AI::STOP)
{
	
}

std::pair<Tetromino, double> AI::itsShowtime(Board& board, std::vector<Tetromino> tetrominos, unsigned int currentTetrominoIdx)
{
	Tetromino bestTetromino(Tetromino::I);
	double bestScore = -1000000.0;

	for(int rotation = 0; rotation < 4; ++rotation)
	{
		Tetromino t = tetrominos[currentTetrominoIdx];
		t.rotate(rotation);

		while(board.canMoveLeft(t))
			t.move(-1, 0);

		while(board.canMoveRight(t))
		{
			Tetromino t2 = t;

			while(board.canMoveDown(t2))
				t2.move(0, 1);

			Board b = board;
			b.merge(t2);

			double score;
			if(currentTetrominoIdx < (tetrominos.size() - 1))
			{
				std::pair<Tetromino, double> result = itsShowtime(b, tetrominos, currentTetrominoIdx + 1);
				score = result.second;
			}
			else
				score = heightWeight * b.aggregateHeight() + linesWeight * b.completeLines() + holesWeight * b.holes() + bumpinessWeight * b.bumpiness();

			if(score > bestScore)
			{
				bestScore = score;
				bestTetromino = t2;
			}

			t.move(1, 0);
		}
	}

	return std::make_pair(bestTetromino, bestScore);
}

