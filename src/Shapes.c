//
// Created by Decimation on 4/8/2018.
//

#include "Shapes.h"
#include "Library.h"

void autoRound_Sphere(sphere_t* sp)
{
	sp->radius       = RoundIEEE754(sp->radius);
	sp->volume       = RoundIEEE754(sp->volume);
	sp->diameter     = RoundIEEE754(sp->diameter);
	sp->surface_area = RoundIEEE754(sp->surface_area);
}

void autoRound_Circle(circle_t* c)
{
	c->radius        = RoundIEEE754(c->radius);
	c->area          = RoundIEEE754(c->area);
	c->diameter      = RoundIEEE754(c->diameter);
	c->circumference = RoundIEEE754(c->circumference);
}

void autoRound_Square(square_t* sq)
{
	sq->area          = RoundIEEE754(sq->area);
	sq->side          = RoundIEEE754(sq->side);
	sq->diagonal_area = RoundIEEE754(sq->diagonal_area);
	sq->diagonal      = RoundIEEE754(sq->diagonal);
	sq->perimeter     = RoundIEEE754(sq->perimeter);
}