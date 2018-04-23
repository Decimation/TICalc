//
// Created by Decimation on 4/7/2018.
//

#ifndef TICALC_TRIGONOMETRY_H
#define TICALC_TRIGONOMETRY_H

#include "C:\CEdev\include\tice.h"
#include "C:\CEdev\include\stddef.h"
#include "C:\CEdev\include\fileioc.h"
#include "C:\CEdev\include\graphx.h"
#include "Library.h"
#include "IO.h"
#include "C:\CEdev\include\stdbool.h"
#include "GraphicsExt.h"

#define ROUND 2
#define DIGIT_THRESHOLD 6

typedef struct {
	bool a, b, c;
	bool A, B, C;
	bool complete;
	bool isSSA;
} trigstatus_t;


// Area = (1/2)|det[xA xB xC  ] |
//				   [ yA yB yC ] |
//				   [ 1	1	1 ] |
void AreaFrom3Points();


void gfx_DrawTriangleSides();

void ClearTrianglePoints();

void RoundTriangle(uint8_t places);


void Synchronize();

void SelectSide();

void SelectAngle();

void RedrawTriangle();

void trig_SolveTriangle();

void trig_Quit();

void trig_CheckSolvability();

void dbg_printTriangle();

void TruncateLabels(int len);

void disp_TriangleData();

void trig_SolveMissingAngle();

//void trig_SolveAAS();
void trig_SolveSSS();

void trig_Reset();

#endif //TICALC_TRIGONOMETRY_H
