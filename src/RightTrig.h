//
// Created by Decimation on 4/14/2018.
//

#ifndef TICALC_RIGHTTRIG_H
#define TICALC_RIGHTTRIG_H

#include "Library.h"
#include "Shapes.h"

void trig_SolveRightTriangle();

void right_SelectAngle();

void sohcahtoa_DrawNull();

void Redraw();

void sohcahtoa_DrawBBB();

void sohcahtoa_DrawAAA();

void pythag_CheckSolvability();

void right_Sync();

void disp_Simplified(real_t* r);

void right_TruncateLabels(int len);

void right_RoundTriangle(uint8_t places);

void sp_SetFuncDataLabel(real_t sideX, real_t sideY, int i);

void sp_SetFuncData2Label(real_t sideX, real_t sideY, int i);

void CheckForInt(char* in, char* possibleSrc);

#endif //TICALC_RIGHTTRIG_H
