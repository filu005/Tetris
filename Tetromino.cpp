#include "Painter.hpp"
#include "Tetromino.hpp"

const char* Tetromino::shapes[7] =
{
	"  8 " // I
	"  8 "
	"  8 "
	"  8 ",

	"  8 " // J
	"  8 "
	" 88 "
	"    ",

	" 8  " // L
	" 8  "
	" 88 "
	"    ",

	"    " // O
	" 88 "
	" 88 "
	"    ",

	"  8 " // S
	" 88 "
	" 8  "
	"    ",

	" 8  " // Z
	" 88 "
	"  8 "
	"    ",

	"    " // T
	" 888"
	"  8 "
	"    "
};

Tetromino::Tetromino(Name name) : _name(name), _x(5), _y(0), _angle(0)
{

}

void Tetromino::paint(Painter& p) const
{
	p.paint(*this);
}

unsigned int Tetromino::getName(void) const
{
	return _name;
}

bool Tetromino::map(int x, int y) const
{
	static const struct
	{
		int x, y;
	} ROTATE[][16] = {
		{
			{ 0, 0 }, { 0, 1 }, { 0, 2 }, { 0, 3 },
			{ 1, 0 }, { 1, 1 }, { 1, 2 }, { 1, 3 },
			{ 2, 0 }, { 2, 1 }, { 2, 2 }, { 2, 3 },
			{ 3, 0 }, { 3, 1 }, { 3, 2 }, { 3, 3 }
		},
		{
			{ 3, 0 }, { 2, 0 }, { 1, 0 }, { 0, 0 },
			{ 3, 1 }, { 2, 1 }, { 1, 1 }, { 0, 1 },
			{ 3, 2 }, { 2, 2 }, { 1, 2 }, { 0, 2 },
			{ 3, 3 }, { 2, 3 }, { 1, 3 }, { 0, 3 }
		},
		{
			{ 3, 3 }, { 3, 2 }, { 3, 1 }, { 3, 0 },
			{ 2, 3 }, { 2, 2 }, { 2, 1 }, { 2, 0 },
			{ 1, 3 }, { 1, 2 }, { 1, 1 }, { 1, 0 },
			{ 0, 3 }, { 0, 2 }, { 0, 1 }, { 0, 0 }
		},
		{
			{ 0, 3 }, { 1, 3 }, { 2, 3 }, { 3, 3 },
			{ 0, 2 }, { 1, 2 }, { 2, 2 }, { 3, 2 },
			{ 0, 1 }, { 1, 1 }, { 2, 1 }, { 3, 1 },
			{ 0, 0 }, { 1, 0 }, { 2, 0 }, { 3, 0 }
		}
	};
	bool val = shapes[_name]
		[ROTATE[_angle][y * 4 + x].y * 4 + ROTATE[_angle][y * 4 + x].x] != ' ';

	return val;
}

void Tetromino::move(int x, int y)
{
	_x += x;
	_y += y;
}

void Tetromino::rotate(int angle)
{
	_angle = (_angle + angle + 4) % 4;
}

