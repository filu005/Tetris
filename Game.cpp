#include "Game.hpp"

Game::Game(int widthInBlocks, int heightInBlocks, GLfloat blockSize) : interval(1.0), _points(0)
{
	_board = std::make_shared<Board>(widthInBlocks, heightInBlocks);
	_tetrominos.reserve(2);
	_tetrominoPool.reserve(7);
	fillTetrominoPool();
	_tetrominos.push_back(randTetrominoFromPool());
	_tetrominos.push_back(randTetrominoFromPool());

	_painter.setProjectionHeight((GLfloat) (heightInBlocks * blockSize));
	_painter.setProjectionWidth((GLfloat) (widthInBlocks * blockSize));
}

void Game::paint(void)
{
	_board->paint(_painter);
	_tetrominos[0].paint(_painter);
}

void Game::tick(void)
{
	Tetromino curTet = _tetrominos[0];
	if(_ai.isRunning())
	{
		auto result = _ai.itsShowtime(*_board, _tetrominos, 0);
		curTet = result.first;
	}
	Tetromino t = curTet;
	t.move(0, 1);
	if(_board->collide(t))
	{
		_board->merge(curTet);
		int removeLinesNum = _board->removeLines();
		if(removeLinesNum > 0)
		{
			_points += removeLinesNum;
			std::cout << "wynik: " << _points << "\n";
		}

		_tetrominos[0] = _tetrominos[1];
		_tetrominos[1] = randTetrominoFromPool();

		if(_board->collide(_tetrominos[0]))
			restart();
	}
	else
		_tetrominos[0] = t;
}

Tetromino Game::randTetrominoFromPool(void)
{
	Tetromino rTet(Tetromino::I);

	fillTetrominoPool();

	int tIdx = rand() % _tetrominoPool.size();
	rTet = _tetrominoPool[tIdx];
	_tetrominoPool.erase(_tetrominoPool.begin() + tIdx);
	return rTet;
}

void Game::keyEvent(Direction d)
{
	Tetromino t = _tetrominos[0];
	switch(d)
	{
	case UP: t.rotate(1);
		break;
	case DOWN: t.move(0, 1);
		break;
	case LEFT: t.move(-1, 0);
		break;
	case RIGHT: t.move(1, 0);
		break;
	}
	if(!_board->collide(t))
		_tetrominos[0] = t;
}

void Game::fillTetrominoPool(void)
{
	if(_tetrominoPool.size() <= 0)
		for(int i = 0; i < 7; ++i)
			_tetrominoPool.push_back(Tetromino(static_cast<Tetromino::Name>(i)));
}

void Game::restart(void)
{
	std::cout << "end game.\n";
	_points = 0;
	_board = make_shared<Board>(_board->getWidth(), _board->getHeight() - 2);

	_tetrominos.erase(_tetrominos.begin(), _tetrominos.end());
	_tetrominoPool.erase(_tetrominoPool.begin(), _tetrominoPool.end());
	fillTetrominoPool();
	_tetrominos.push_back(randTetrominoFromPool());
	_tetrominos.push_back(randTetrominoFromPool());
}

