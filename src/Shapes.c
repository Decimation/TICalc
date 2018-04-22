//
// Created by Decimation on 4/8/2018.
//

#include "Shapes.h"
#include "Library.h"

static const int g_Digits = 3;

void autoRound_Sphere(sphere_t* sp)
{
	os_RealRound(&sp->radius, g_Digits);
	os_RealRound(&sp->diameter, g_Digits);
	os_RealRound(&sp->surface_area, g_Digits);
	os_RealRound(&sp->volume, g_Digits);
}

void autoRound_Circle(circle_t* c)
{
	os_RealRound(&c->radius, g_Digits);
	os_RealRound(&c->diameter, g_Digits);
	os_RealRound(&c->area, g_Digits);
	os_RealRound(&c->circumference, g_Digits);
}

void autoRound_Square(square_t* sq)
{
	os_RealRound(&sq->side, g_Digits);
	os_RealRound(&sq->area, g_Digits);
	os_RealRound(&sq->perimeter, g_Digits);
	os_RealRound(&sq->diagonal, g_Digits);
	os_RealRound(&sq->diagonal_area, g_Digits);
}