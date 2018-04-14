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

real_t io_gfx_ReadReal(superpoint_t vBuffer);
void xprint(superpoint_t p);
void Clear(superpoint_t p);
bool PointEq(superpoint_t a, superpoint_t b);
void trig_ClearAngleX(superpoint_t p);
void trig_HighlightAngleX(superpoint_t p);
void trig_SolveRightTriangle();

#endif //TICALC_TRIGONOMETRY_H
