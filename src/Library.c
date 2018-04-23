/* Keep these headers */

#include <math.h>
#include "C:\CEdev\include\stddef.h"
#include "C:\CEdev\include\stdbool.h"
#include "C:\CEdev\include\fileioc.h"
#include "Library.h"
#include "IO.h"


/**
 * THESE MUST BE GLOBAL OR ELSE EXITING
 * THE ENTRY POINT WILL CAUSE AN NMI RESET
 */
char g_response[RESP_SIZE];
char g_inputBuffer[INPUT_SIZE];
//int24_t g_value;


void sys_GarbageCollect()
{
	dbg_sprintf(dbgout, "[DECIMATH] Freeing pointers\n");
	free(g_X);
	dbg_sprintf(dbgout, "[DECIMATH] Unloaded\n");
	os_ClrHome();
}

void EchoInput(int i)
{
	//sprintf(g_response, "(%d)", i);
	//io_print(g_response, 15, 0);
}

void Substring(char* in, int index, int len, char* out)
{

	memcpy(out, &in[index], len + 1);
	out[len] = '\0';
}

void Prepend(char* s, const char* t)
{
	size_t len = strlen(t);
	size_t i;

	memmove(s + len, s, strlen(s) + 1);

	for (i = 0; i < len; ++i)
	{
		s[i] = t[i];
	}
}

int IndexOf(char* values, char find)
{
	int index;
	const char* ptr = strchr(values, find);
	if (ptr)
	{
		index = (int) (ptr - values);
	}
	else index = -1;
	return index;
}

int StrCut(char* str, int begin, int len)
{
	int l = strlen(str);

	if (len < 0) len         = l - begin;
	if (begin + len > l) len = l - begin;
	memmove(str + begin, str + begin + len, l - len + 1);

	return len;
}

int IsEven(double d)
{
	double int_part;
	modf(d / 2.0, &int_part);
	return 2.0 * int_part == d;
}

double RoundIEEE754(double d)
{
	double i = floor(d);
	d -= i;
	if (d < 0.5)
		return i;
	if (d > 0.5)
		return i + 1.0;
	if (IsEven(i))
		return i;
	return i + 1.0;
}

bool os_RadiansMode() {
	const real_t real90  = os_Int24ToReal(90);
	const real_t real1   = os_Int24ToReal(1);
	real_t       buf     = os_RealSinRad(&real90);
	if (os_RealCompare(&buf, &real1) == 0)
	{
		//dbg_sprintf(dbgout, "[DECIMATH] [Info] Degrees mode\n");
		return false;
	}
	else
	{
		//dbg_sprintf(dbgout, "[DECIMATH] [Info] Radians mode\n");
		return true;
	}
}

void mem_Zero(char* ptr, int c)
{
	int i = 0;
	dbg_sprintf(dbgout, "[dbg] [mem_Zero] Zeroing memory from 0x%p to 0x%p\n", (void*) ptr, &ptr + c);
	for (; i < c; i++)
	{
		ptr[i] = (char) NULL;
	}

}

