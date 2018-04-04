//
// Created by Decimation on 4/3/2018.
//

#include "IO.h"

/**
 * NOTES
 * - Variables must be declared at the first lines of the current scope
 * - All branching statements must use braces, whether or not the inner scope is only one line in length
 * - The format specifiers %f, %g, and %e do not work for any printf-related functions
 * TODO
 * - Figure out why I need my fields to be global
 * - Integers seem to need to be int24_t or any other fixed-size type, rather than keywords such as int or short
 * - Strings seem to need to be const char*
 */

int Menu()
{
	int i;
	os_ClrHome();
	println("Rip and tear", 0, 0);
	println("1:Area", 0, 1);
	println("2:Surface area", 0, 2);
	println("3:Volume", 0, 3);
	println("4:Formulas", 0, 4);
	println("5:Polygons", 0, 5);
	println("6:Simplifiers", 0, 6);
	println("7: ...", 0, 7);
	println("8: ...", 0, 8);
	println("", 0, 9);

	i = os_GetNumberInput("] ");
	sprintf(g_response, "] > %d <", i);
	print(g_response, 0, 9);
	return i;
}


void TestInput()
{
	int   i;
	float x;

	os_ClrHome();
	os_GetStringInput("Enter a string ", g_inputBuffer, INPUT_SIZE);
	sprintf(g_response, "Echo: %s", g_inputBuffer);
	print(g_response, 0, 2);

	while (!os_GetCSC());

	os_ClrHome();

	i = os_GetNumberInput("Enter an int ");
	sprintf(g_response, "Echo: %d", i);
	print(g_response, 0, 2);

	while (!os_GetCSC());
	os_ClrHome();
	x = os_GetFloatInput("Enter 3.14 ");
	if (x == 3.14)
	{
		print("OK", 0, 1);
	}
	PutFloat(x, 0, 2);
}


// sqrt(2) = 1.414213562
void main(void) // NOLINT
{

	// sqrt(2) = 1.414213562

	TestInput();
	os_ClrHome();


	/* Wait for a key press before quitting */
	while (!os_GetCSC());
}