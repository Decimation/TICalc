//
// Created by Decimation on 4/3/2018.
//




#ifndef TICALC_LIBRARY_H
#define TICALC_LIBRARY_H


#include <string.h>
#include <stdio.h>
#include <math.h>
#include "C:\CEdev\include\tice.h"
#include "C:\CEdev\include\fileioc.h"
#include "C:\CEdev\include\stdint.h"
//#include "IO.h"
#include "C:\CEdev\include\debug.h"

/* Make sure to adjust those sizes according to your usage! */
#define INPUT_SIZE  10
#define RESP_SIZE   20

extern char g_response[RESP_SIZE];
extern char g_inputBuffer[INPUT_SIZE];


//extern int24_t g_value;

void sys_GarbageCollect();

int IsEven(double d);

double RoundIEEE754(double d);

void Substring(char* in, int index, int len, char* out);

void EchoInput(int i);

void Zero(char* ptr, int c);

/**
 * Prepends t into s. Assumes s has enough space allocated
 * for the combined string.
 * @param s
 * @param t
 */
void Prepend(char* s, const char* t);

int IndexOf(char* values, char find);

/*
 * Remove given section from string. Negative len means remove
 * everything up to the end.
 */
int StrCut(char* str, int begin, int len);

#endif //TICALC_LIBRARY_H
