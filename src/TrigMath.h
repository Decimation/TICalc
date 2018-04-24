//
// Created by Decimation on 4/22/2018.
//

#ifndef TICALC_TRIGMATH_H
#define TICALC_TRIGMATH_H

#include "C:\CEdev\include\tice.h"
#include "C:\CEdev\include\stddef.h"
//#include "C:\CEdev\include\stdbool.h"
#include "C:\CEdev\include\fileioc.h"
#include "C:\CEdev\include\graphx.h"
#include "Library.h"
#include "IO.h"
#include "C:\CEdev\include\stdbool.h"
#include "MathLib.h"

float SinDeg(float f);

float ASinDeg(float f);

float CosineDeg(float f);

real_t os_RealSinDeg(real_t r);

real_t os_RealAcosAuto(real_t r);

real_t los_Side_x(real_t X, real_t y, real_t Y);

real_t los_Angle_x(real_t x, real_t Y, real_t y);

real_t loc_Side_x(real_t a, real_t b, real_t angle);

real_t loc_AngleA(real_t b, real_t c, real_t a);

real_t loc_AngleB(real_t c, real_t a, real_t b);

#endif //TICALC_TRIGMATH_H
