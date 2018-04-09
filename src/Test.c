//
// Created by Decimation on 4/4/2018.
//

#include "Test.h"

void TestRead()
{
	int   i;
	float x;
	real_t r;

	/**
	 * Test custom-made IO functions
	 */

	os_ClrHome();
	print("Alpha", 0, 3);
	ReadLineAlpha(g_inputBuffer);
	sprintf(g_response, "Echo: %s", g_inputBuffer);
	print(g_response, 0, 1);

	while (!os_GetCSC());
	os_ClrHome();

	print("Digit", 0, 3);
	ReadLineDigit(g_inputBuffer);
	sprintf(g_response, "Echo: %s", g_inputBuffer);
	print(g_response, 0, 1);

	while (!os_GetCSC());
	os_ClrHome();

	print("Float",0,3);
	x = ReadFloat();
	r = os_FloatToReal(x);
	os_RealToStr(g_response, &r, 0, 0, -1);
	print(g_response,0,1);
	//FloatToStringPretty(x, 5, g_inputBuffer);
	//print(g_inputBuffer, 0, 1);

	while (!os_GetCSC());
	os_ClrHome();

	print("Int",0,3);
	i = ReadInt();
	sprintf(g_response, "%d", i);
	print(g_response, 0, 1);
	while (!os_GetCSC());
	os_ClrHome();
}