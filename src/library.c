/* Keep these headers */

#include <math.h>
#include "C:\CEdev\include\stddef.h"
#include "C:\CEdev\include\stdbool.h"
#include "C:\CEdev\include\tice.h"
#include "C:\CEdev\include\fileioc.h"
#include "C:\CEdev\include\stdint.h"
#include "../../../../../CEdev/include/tice.h"
#include "library.h"
#include <string.h>
#include <stdio.h>
/* Make sure to adjust those sizes according to your usage! */
#define INPUT_SIZE  10
#define RESP_SIZE   20

/* Draw text on the homescreen at the given X/Y location */
void print(const char* text, uint8_t xpos, uint8_t ypos)
{
	os_SetCursorPos(ypos, xpos);
	os_PutStrFull(text);
}

bool IsPrime(int24_t number)
{
	int24_t i;
	if (number == 1)
	{
		return false;
	}

	for (i = 2; i < number; i++)
	{
		if (number % i == 0 && i != number) return false;
	}
	return true;
}

int24_t HighestOneBit(int24_t num)
{
	int24_t ret;
	if (!num)
	{
		return 0;
	}

	ret = 1;

	while (num >>= 1)
	{
		ret <<= 1;
	}

	return ret;
}

/**
 *
 * @param n the number of people standing in the circle
 * @return the safe position who will survive the execution
 *   f(N) = 2L + 1 where N =2^M + L and 0 <= L < 2^M
 */
int24_t getSafePosition(int24_t n)
{
	// find value of L for the equation
	int24_t valueOfL     = n - HighestOneBit(n);
	int24_t safePosition = 2 * valueOfL + 1;

	return safePosition;
}

/**
 * THESE MUST BE GLOBAL OR ELSE EXITING
 * THE ENTRY POINT WILL CAUSE AN NMI RESET
 */
char    g_response[RESP_SIZE];
char    g_inputBuffer[INPUT_SIZE];
int24_t g_value;

int24_t os_GetNumberInput(const char* prompt)
{
	/* Ask the user to type a string, which gets stored in inputBuf */
	os_GetStringInput(prompt, g_inputBuffer, INPUT_SIZE);
	return atoi(g_inputBuffer);
}



float os_GetNumberInputF(const char* prompt)
{
	/* Ask the user to type a string, which gets stored in inputBuf */
	os_GetStringInput(prompt, g_inputBuffer, INPUT_SIZE);

	// Prints okay, but why won't atof work?!
	g_inputBuffer[indexOf(g_inputBuffer,':')] = '.';
	print(g_inputBuffer, 0,1);



	return atof(g_inputBuffer);
}

#include <math.h>

float FindRoot(float d)
{
	char out[10];
	float step;
	step = 0.1;

	while (sqrt(step) != d)
	{
		step += 0.1;
		if (sqrt(step) > d)
			return -1;
	}
	return step;
}


/**
 * NOTES
 * - Variables must be declared at the first lines of the current scope
 * - All branching statements must use braces, whether or not the inner scope is only one line in length
 * TODO
 * - Figure out why I need my fields to be global
 * - Integers seem to need to be int24_t or any other fixed-size type, rather than keywords such as int or short
 * - Strings seem to need to be const char*
 */

void clear(char* buf, int size) {
	int i;
	i = 0;
	while (i < size) {
		buf[i] = 0;
		i++;
	}
}


void main(void) // NOLINT
{
	float x;
	/* Clear the homescreen */
	os_ClrHome();


	os_GetStringInput("Enter a string ", g_inputBuffer, INPUT_SIZE);
	sprintf(g_response, "Echo: %s", g_inputBuffer);
	print(g_response, 0,2);

	while (!os_GetCSC());

	g_value = os_GetNumberInput("Enter an int ");
	sprintf(g_response, "Echo: %d", g_value);
	print(g_response,0,2);

	while (!os_GetCSC());

	// sqrt(2) = 1.414213562

	x = os_GetNumberInputF("Enter a float ");
	sprintf(g_response, "Echo: %e", x);
	print(g_response,0,2);

	while (!os_GetCSC());

	clear(g_inputBuffer, INPUT_SIZE);
	clear(g_response, RESP_SIZE);

	os_GetStringInput("Try again ", g_inputBuffer, INPUT_SIZE);
	g_inputBuffer[indexOf(g_inputBuffer, ':')] = '.';
	print(g_inputBuffer, 0,1);
	x = (float) atof(g_inputBuffer);
	if (x == 3.14)
	{
		print("ok",0,3);
	}
	sprintf(g_inputBuffer, "%g", x);
	print(g_inputBuffer,0,2);

	//sprintf(g_response, "Echo: %s | %d | %c", g_inputBuffer, (unsigned int)*g_inputBuffer, (unsigned char) *g_inputBuffer);
	//g_value = os_GetNumberInput("N? ");

	/* Build the user response */
	//sprintf(g_response, "N: %d | JOSEPHUS: %d | PRIME: %s", g_value, getSafePosition((int24_t)g_value), IsPrime((int24_t)g_value) ? "YES" : "NO");


	/* Clear the homescreen and display the built response */
	//os_ClrHome();
	//print(g_response, 0, 0);

	/* Wait for a key press before quitting */
	while (!os_GetCSC());
}
