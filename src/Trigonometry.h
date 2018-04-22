//
// Created by Decimation on 4/7/2018.
//

#ifndef TICALC_TRIGONOMETRY_H
#define TICALC_TRIGONOMETRY_H

#include "C:\CEdev\include\tice.h"
#include "C:\CEdev\include\stddef.h"
//#include "C:\CEdev\include\stdbool.h"
#include "C:\CEdev\include\fileioc.h"
#include "C:\CEdev\include\graphx.h"
#include "Library.h"
#include "IO.h"
#include "C:\CEdev\include\stdbool.h"

typedef struct {
	bool a, b, c;
	bool A, B, C;
} trigstatus_t;

typedef struct {
	real_t A, B, C;
	real_t a, b, c;
	real_t area;
} triangle_t;

typedef struct {
	gfx_point_t point;
	char        label[20];
} superpoint_t;

// Area = (1/2)|det[xA xB xC  ] |
//				   [ yA yB yC ] |
//				   [ 1	1	1 ] |
void AreaFrom3Points();

void dbg_Superpoint(superpoint_t* p);

real_t os_RealAcosDeg(real_t r);

void ClearTrianglePoints();

void RoundTriangle();

void sp_SetLabel(superpoint_t* p, const char* s);

void Synchronize();

void SelectSide();

void SelectAngle();

void RedrawTriangle();

real_t loc_AngleA(real_t b, real_t c, real_t a);

real_t loc_AngleB(real_t c, real_t a, real_t b);

real_t io_gfx_ReadReal(superpoint_t* vBuffer);

void gfx_Print(superpoint_t* p);

void Clear(superpoint_t* p);

bool PointEq(superpoint_t a, superpoint_t b);

void gfx_ClearHighlight(superpoint_t* p);

void gfx_HighlightPoint(superpoint_t* p);

void trig_SolveTriangle();

void trig_Quit();

void trig_CheckSolvability();

void dbg_printTriangle();

void trig_SolveSSS();

#endif //TICALC_TRIGONOMETRY_H
