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


static const double UpperBounds = 1e99;
static const double LowerBounds = -1e99;
int SolveForX(char* eq) {
	double x = LowerBounds;
	os_ClrHome();


	while (x <= UpperBounds && x >= LowerBounds) {

	}
}

int Menu()
{
	int i;
	os_ClrHome();
	println("Rip and tear",0,0);
	println("1:Area", 0, 1);
	println("2:Surface area", 0, 2);
	println("3:Volume", 0, 3);
	println("4:Formulas",0,4);
	println("5:Polygons",0,5);
	println("6:Simplifiers",0,6);
	println("7: ...",0,7);
	println("8: ...",0,8);
	println("",0,9);

	i = os_GetNumberInput("] ");
	sprintf(g_response, "] > %d <", i);
	print(g_response, 0,9);
	return i;
}



void main(void) // NOLINT
{
	int i = Menu();


	/* Clear the homescreen */
	//os_ClrHome();

	/* Wait for a key press before quitting */
	while (!os_GetCSC());
}