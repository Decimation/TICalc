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

extern char    g_response[RESP_SIZE];
extern char    g_inputBuffer[INPUT_SIZE];
//extern int24_t g_value;


/**
 * Prepends t into s. Assumes s has enough space allocated
 * for the combined string.
 * @param s
 * @param t
 */
void prepend(char* s, const char* t);

int indexOf(char* values, char find);

char intToChar(int c);

int GetMantissa(float f);

/*
 * Remove given section from string. Negative len means remove
 * everything up to the end.
 */
int str_cut(char* str, int begin, int len);

float StringToFloat(char* in);


#define MAX_PRECISION    (10)
static const double rounders[MAX_PRECISION + 1] =
{
		0.5,                // 0
		0.05,                // 1
		0.005,                // 2
		0.0005,                // 3
		0.00005,            // 4
		0.000005,            // 5
		0.0000005,            // 6
		0.00000005,            // 7
		0.000000005,        // 8
		0.0000000005,        // 9
		0.00000000005        // 10
};

char* FloatToString(double f, char* buf, int precision);

#endif //TICALC_LIBRARY_H
