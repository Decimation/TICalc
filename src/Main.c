//
// Created by Decimation on 4/3/2018.
//


#include "C:\CEdev\include\fileioc.h"
#include "Menu.h"
#include "Test.h"
#include "C:\CEdev\include\debug.h"
#include "Trigonometry.h"
#include "MathLib.h"
#include "RightTrig.h"


#define MAJOR 0
#define MINOR 8

/**
 * NOTES
 * - Variables must be declared at the first lines of the current scope
 * - All branching statements must use braces, whether or not the inner scope is only one line in length
 * - The format specifiers %f, %g, and %e do not work for any printf-related functions
 * TODO: Use real_t instead of float and doubles now
 */
#define DEBUG
#undef DEBUG

void Info(void) // NOLINT
{
	dbg_sprintf(dbgout, "[DECIMATH] [Info] Build %d.%d\n", MAJOR, MINOR);
	//dbg_sprintf(dbgout, "[DECIMATH] Big nigga initialized\n");
	dbg_sprintf(dbgout, "[DECIMATH] [Info] Mode: %s\n", os_RadiansMode() ? "Radians" : "Degrees");
	dbg_sprintf(dbgout, "[DECIMATH] [Info] sizeof(real_t) = %d\n", sizeof(real_t));
}

void main(void) // NOLINT
{
	int i;
	Info();
#ifdef DEBUG
	TestRead();
#else
	i = menu_Main();

	if (i == 1) menu_Area();
	if (i == 6) menu_Simplifiers();
	if (i == 7) menu_More();
	if (i == 0) trig_SolveTriangle();
	if (i == -1) trig_SolveRightTriangle();

	sys_GarbageCollect();
#endif


}