//
// Created by Decimation on 4/3/2018.
//


#include "C:\CEdev\include\tice.h"
#include "C:\CEdev\include\fileioc.h"
#include "Menu.h"
#include "Test.h"

/**
 * NOTES
 * - Variables must be declared at the first lines of the current scope
 * - All branching statements must use braces, whether or not the inner scope is only one line in length
 * - The format specifiers %f, %g, and %e do not work for any printf-related functions
 */


void main(void) // NOLINT
{
	//TestRead();

	int i = menu_Main();

	if (i == 1) menu_Area();
	if (i == 6) menu_Simplifiers();
	if (i == 7) menu_More();

	free(g_inputBuffer);
	free(g_response);


}