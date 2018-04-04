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

#include <math.h>

/**
 * Converts a decimal to a square root
 * @param d
 * @return
 */
float DecimalToRoot(float d);

void DecimalToPi(float f, char* out);

float Ceil(float);
#endif //TICALC_SIMPLIFIERS_H
