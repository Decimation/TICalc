//
// Created by Decimation on 4/4/2018.
//

#include "Test.h"
#include "C:\CEdev\include\debug.h"

void TestRead()
{
	int    i;
	float  x;
	real_t r;

	/**
	 * Test custom-made IO functions
	 */

	os_ClrHome();
	io_print("Alpha", 0, 3);
	io_ReadLineAlpha(g_inputBuffer);
	sprintf(g_response, "Echo: %s", g_inputBuffer);
	dbg_sprintf(dbgout, "[DECIMATH] Echo: %s\n", g_inputBuffer);
	io_print(g_response, 0, 1);

	while (!os_GetCSC());
	os_ClrHome();

	io_print("Digit", 0, 3);
	io_ReadLineDigit(g_inputBuffer);
	sprintf(g_response, "Echo: %s", g_inputBuffer);
	dbg_sprintf(dbgout, "[DECIMATH] Echo: %s\n", g_inputBuffer);
	io_print(g_response, 0, 1);
	//sprintf(g_response, "First char: 0x%X", *g_inputBuffer);
	dbg_sprintf(dbgout, "[DECIMATH] First char: 0x%X\n", *g_inputBuffer);
	io_print(g_response, 0, 2);

	while (!os_GetCSC());
	os_ClrHome();

	io_print("Float", 0, 3);
	x = io_ReadFloat();
	r = os_FloatToReal(x);
	os_RealToStr(g_response, &r, 0, 0, -1);
	io_print(g_response, 0, 1);
	//FloatToStringPretty(x, 5, g_inputBuffer);
	//io_print(g_inputBuffer, 0, 1);

	while (!os_GetCSC());
	os_ClrHome();

	io_print("Real", 0, 3);
	r = io_ReadReal();
	os_RealToStr(g_response, &r, 0, 0, -1);
	io_print(g_response, 0, 1);
	//FloatToStringPretty(x, 5, g_inputBuffer);
	//io_print(g_inputBuffer, 0, 1);

	while (!os_GetCSC());
	os_ClrHome();

	io_print("Int", 0, 3);
	i = io_ReadInt();
	dbg_sprintf(dbgout, "[DECIMATH] io_ReadInt(): %d\n", i);
	sprintf(g_response, "%d", i);
	io_print(g_response, 0, 1);
	while (!os_GetCSC());
	os_ClrHome();
}