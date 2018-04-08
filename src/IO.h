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

float os_GetFloatInput(const char* prompt);

void ReadLineDigit(char* buffer);

void ReadLineAlpha(char* buffer);

float ReadFloat();

int ReadInt();

void ClearLine(uint8_t x, uint8_t y);

void ClearFirstLine();


#endif //TICALC_IO_H
