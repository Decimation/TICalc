//
// Created by Decimation on 4/8/2018.
//

#ifndef TICALC_SHAPES_H
#define TICALC_SHAPES_H

typedef struct {
	float radius;
	float area;
	float circumference;
	float diameter;
} circle_t;

typedef struct {
	float side;
	float perimeter;
	float area;
	float diagonal;
	float diagonal_area;
} square_t;

typedef struct {
	float radius;
	float diameter;
	float volume;
	float surface_area;
} sphere_t;

void autoRound_Circle(circle_t* c);

void autoRound_Square(square_t* sq);

void autoRound_Sphere(sphere_t* sp);

#endif //TICALC_SHAPES_H
