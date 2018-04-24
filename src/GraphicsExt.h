//
// Created by Decimation on 4/22/2018.
//

#ifndef TICALC_GRAPHICSEXT_H
#define TICALC_GRAPHICSEXT_H

#include "Library.h"
#include "Shapes.h"

void gfx_Print(superpoint_t* p);

void gfx_Clear(superpoint_t* p);

real_t io_gfx_ReadReal(superpoint_t* vBuffer);

bool PointEq(superpoint_t a, superpoint_t b);

void sp_SetLabel(superpoint_t* p, const char* s);

void gfx_ClearHighlight(superpoint_t* p);

void gfx_HighlightPoint(superpoint_t* p);

void gfx_PrintColor(superpoint_t* p, uint8_t color);

#endif //TICALC_GRAPHICSEXT_H
