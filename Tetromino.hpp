#pragma once
#include "PainterSquare.hpp"

class Painter;

// http://tetris.wikia.com/wiki/Tetris_Guideline

class Tetromino
{
public:
	enum Name { I, O, T, S, Z, J, L };

	Tetromino(Name name);
	
	void paint(Painter& p) const;
	bool map(int x, int y) const;
	void move(int x, int y);
	void rotate(int angle);
	unsigned int getName() const;
	unsigned int x() const { return _x; }
	unsigned int y() const { return _y; }

private:
	unsigned int _name;
	unsigned int _x, _y;
	int _angle;

	static const char* shapes[7];
};