//
// Created by Decimation on 4/3/2018.
//

#ifndef TICALC_IO_H
#define TICALC_IO_H

#include "Library.h"
#include "C:\CEdev\include\tice.h"
#include "C:\CEdev\include\fileioc.h"
#include "C:\CEdev\include\stdint.h"

void PutFloat(float f, uint8_t xpos, uint8_t ypos);


/* Draw text on the homescreen at the given X/Y location */
void print(const char* text, uint8_t xpos, uint8_t ypos);

void println(const char* text, uint8_t xpos, uint8_t ypos);

int24_t os_GetNumberInput(const char* prompt);

/**
 * Floats read-in will still be read properly within C but will not
 * print out properly for whatever fucking reason
 * @param prompt
 * @return
 */
float os_GetFloatInput(const char* prompt);

void ReadLine(char* buffer);
#endif //TICALC_IO_H
