//
// Created by Decimation on 4/8/2018.
//

#ifndef TICALC_SHAPES_H
#define TICALC_SHAPES_H

#include "C:\CEdev\include\tice.h"
#include "Library.h"

typedef struct {
	real_t radius;
	real_t area;
	real_t circumference;
	real_t diameter;
} circle_t;

typedef struct {
	real_t side;
	real_t perimeter;
	real_t area;
	real_t diagonal;
	real_t diagonal_area;
} square_t;

typedef struct {
	real_t radius;
	real_t diameter;
	real_t volume;
	real_t surface_area;
} sphere_t;

typedef struct {
	gfx_point_t point;
	char        label[20];
} superpoint_t;

typedef struct {
	real_t A, B, C;
	real_t a, b, c;
	real_t area;
} triangle_t;

typedef struct {
	bool a, b, c;
	bool A, B, C;
	bool complete;
	bool isSSA;
} trigstatus_t;

void autoRound_Circle(circle_t* c);

void autoRound_Square(square_t* sq);

void autoRound_Sphere(sphere_t* sp);

#endif //TICALC_SHAPES_H
