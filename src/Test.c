//
// Created by Decimation on 4/4/2018.
//

#include "Test.h"

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

void TestRead()
{
	int   i;
	float x;

	/**
	 * Test custom-made IO functions
	 */

	os_ClrHome();
	ReadLineAlpha(g_inputBuffer);
	sprintf(g_response, "Echo: %s", g_inputBuffer);
	print(g_response, 0, 1);

	while (!os_GetCSC());
	os_ClrHome();
	ReadLineDigit(g_inputBuffer);
	sprintf(g_response, "Echo: %s", g_inputBuffer);
	print(g_response, 0, 1);

	while (!os_GetCSC());
	os_ClrHome();

	Zero(g_response, RESP_SIZE);
	Zero(g_inputBuffer, INPUT_SIZE);

	x = ReadFloat();
	FloatToStringPretty(x, 5, g_inputBuffer);
	print(g_inputBuffer, 0, 1);

	while (!os_GetCSC());
	os_ClrHome();

	i = ReadInt();
	sprintf(g_response, "%d", i);
	print(g_response, 0, 1);
	while (!os_GetCSC());
	os_ClrHome();
}