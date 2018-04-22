//
// Created by Decimation on 4/3/2018.
//


#include "C:\CEdev\include\fileioc.h"
#include "Menu.h"
#include "Test.h"
#include "C:\CEdev\include\debug.h"
#include "Trigonometry.h"
#include "MathLib.h"
/**
 * NOTES
 * - Variables must be declared at the first lines of the current scope
 * - All branching statements must use braces, whether or not the inner scope is only one line in length
 * - The format specifiers %f, %g, and %e do not work for any printf-related functions
 * TODO: Use real_t instead of float and doubles now
 */
#define DEBUG
#undef DEBUG


void Info(void)
{
	char         sbuf[10];
	const real_t real90  = os_Int24ToReal(90);
	const real_t real1   = os_Int24ToReal(1);
	real_t       buf     = os_RealSinRad(&real90);
	real_t       real025 = os_FloatToReal(0.25f);
	if (os_RealCompare(&buf, &real1) == 0)
	{
		dbg_sprintf(dbgout, "[DECIMATH] [Info] Degrees mode\n");
	}
	else
	{
		dbg_sprintf(dbgout, "[DECIMATH] [Info] Radians mode\n");
		os_RealToStr(sbuf, &buf, 0, 0, -1);
		dbg_sprintf(dbgout, "[DECIMATH] [Info] sin(90) = %s\n", sbuf);
	}


	buf = os_RealAcosRad(&real025);
	os_RealToStr(sbuf, &buf, 0, 0, -1);
	dbg_sprintf(dbgout, "[DECIMATH] [Info] acos(0.25) = %s\n", sbuf);

	dbg_sprintf(dbgout, "[DECIMATH] [Info] Build %d.%d\n", 0, 2);
	//dbg_sprintf(dbgout, "[DECIMATH] Big nigga initialized\n");
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

	sys_GarbageCollect();
#endif


}