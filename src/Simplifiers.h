//
// Created by Decimation on 4/3/2018.
//

#ifndef TICALC_SIMPLIFIERS_H
#define TICALC_SIMPLIFIERS_H

#include "C:\CEdev\include\stddef.h"
#include "C:\CEdev\include\stdbool.h"
#include "C:\CEdev\include\tice.h"
#include "C:\CEdev\include\fileioc.h"
#include "C:\CEdev\include\stdint.h"
#include "Library.h"

#include <math.h>

/**
 * Converts a decimal to a square root
 * i.e. sqrt(2) = 1.414213562
 * @param d
 * @return
 */
float DecimalToRoot(float d);

float DecimalToPi(float f);

#endif //TICALC_SIMPLIFIERS_H
