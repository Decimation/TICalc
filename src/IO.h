//
// Created by Decimation on 4/3/2018.
//

#ifndef TICALC_IO_H
#define TICALC_IO_H

#include "Library.h"
#include "C:\CEdev\include\tice.h"
#include "C:\CEdev\include\fileioc.h"
#include "C:\CEdev\include\stdint.h"

extern real_t* g_X;

/* Draw text on the homescreen at the given X/Y location */
void io_print(const char* text, uint8_t xpos, uint8_t ypos);

void io_println(const char* text, uint8_t xpos, uint8_t ypos);

/*int24_t os_GetNumberInput(const char* prompt);
float os_GetFloatInput(const char* prompt);*/

void io_ReadLineDigit(char* buffer);

void io_ReadLineAlpha(char* buffer);

real_t io_ReadReal();

float io_ReadFloat();

int io_ReadInt();

void io_ReadArray(real_t* out, int len);

void io_ClearLine(uint8_t x, uint8_t y);

void io_ClearFirstLine();

real_t io_RclX();

#endif //TICALC_IO_H
