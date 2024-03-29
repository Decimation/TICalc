//
// Created by Decimation on 4/3/2018.
//

#ifndef TICALC_MATHLIB_H
#define TICALC_MATHLIB_H

#include "C:\CEdev\include\stddef.h"
#include "C:\CEdev\include\stdbool.h"
#include "C:\CEdev\include\tice.h"
#include "C:\CEdev\include\fileioc.h"
#include "C:\CEdev\include\stdint.h"
#include <math.h>

/**
 * Checks primality of a number
 * @param number
 * @return
 */
bool IsPrime(int24_t number);

int24_t HighestOneBit(int24_t num);

/**
 * Josephus problem
 * @param n the number of people standing in the circle
 * @return the safe position who will survive the execution
 *   f(N) = 2L + 1 where N =2^M + L and 0 <= L < 2^M
 */
int24_t GetSafePosition(int24_t n);

extern const float PI;
real_t ArcLength(real_t M, real_t r);
void SimplifyRadicalStrFromDecimal(real_t decimal, char* out);

void SimplifyRadicalStr(int24_t insideRoot, char* out);

void SimplifyRadical(int24_t insideRoot, int24_t out[2]);

/**
 * V = 4/3pi(r)^3
 */
real_t volume_Sphere(real_t radius);

/**
 * A = 4pi(r)^2
 */
real_t surfaceArea_Sphere(real_t radius);

#endif //TICALC_MATHLIB_H
