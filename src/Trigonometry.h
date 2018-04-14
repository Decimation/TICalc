//
// Created by Decimation on 4/7/2018.
//

#ifndef TICALC_TRIGONOMETRY_H
#define TICALC_TRIGONOMETRY_H

#include "C:\CEdev\include\tice.h"
#include "C:\CEdev\include\stddef.h"
#include "C:\CEdev\include\stdbool.h"
#include "C:\CEdev\include\fileioc.h"
#include "C:\CEdev\include\graphx.h"
#include "Library.h"
#include "IO.h"

typedef struct {
	gfx_point_t point;
	char* label;
} superpoint_t;

bool PointEq(gfx_point_t a, gfx_point_t b);
void trig_ClearAngle(char* str, gfx_point_t p);
void trig_HighlightAngle(char* str, gfx_point_t p);
void print_t(char* str, gfx_point_t p);
void trig_SolveRightTriangle();

#endif //TICALC_TRIGONOMETRY_H
