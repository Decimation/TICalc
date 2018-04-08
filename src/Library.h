//
// Created by Decimation on 4/3/2018.
//




#ifndef TICALC_LIBRARY_H
#define TICALC_LIBRARY_H


#include <string.h>
#include <stdio.h>
#include <math.h>

/* Make sure to adjust those sizes according to your usage! */
#define INPUT_SIZE  10
#define RESP_SIZE   20

extern char g_response[RESP_SIZE];
extern char g_inputBuffer[INPUT_SIZE];
//extern int24_t g_value;


int IsEven(double d);

double RoundIEEE754(double d);

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

char IntToChar(int c);

int GetMantissa(float f);

/*
 * Remove given section from string. Negative len means remove
 * everything up to the end.
 */
int StrCut(char* str, int begin, int len);

float StringToFloat(char* in);

char* FloatToString2(double n, char* s);

char* FloatToString(double f, char* buf, int precision);

void FloatToStringPretty(float in, int digitLen, char* out);

#endif //TICALC_LIBRARY_H
