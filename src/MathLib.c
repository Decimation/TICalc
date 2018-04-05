//
// Created by Decimation on 4/3/2018.
//


#include "MathLib.h"
#include "IO.h"
#include "Simplifiers.h"

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


int24_t GetSafePosition(int24_t n)
{
	// find value of L for the equation
	int24_t valueOfL     = n - HighestOneBit(n);
	int24_t safePosition = 2 * valueOfL + 1;

	return safePosition;
}

const float PI = 3.141592654f;

void solve_Circle() {
	char buf[5];
	char bigbuf[20];
	int i;
	float radius = 0, area = 0, circumf = 0, diam = 0;
	float given = ReadFloat();
	Zero(g_inputBuffer, INPUT_SIZE);
	println("What was this data?",0,1);
	println("1:Radius",0,2);
	println("2:Area",0,3);
	println("3:Circumference",0,4);
	println("4:Diameter",0,5);
	i = ReadInt();

	if (i == 1) {
		radius = given;
		area = PI * (float) pow(radius, 2);
		diam = radius * 2;
		circumf = PI * diam;
	}

	if (i == 2) {
		area = given;
		radius = (float) sqrt(area) / PI;
		diam = radius * 2;
		circumf = PI * diam;
	}

	if (i == 3) {
		circumf = given;
		diam = circumf / PI;
		radius = diam / 2;
		area = PI * (float) pow(radius, 2);
	}

	if (i == 4) {
		diam = given;
		radius = diam / 2;
		area = PI * (float) pow(radius, 2);
		circumf = PI * diam;
	}

	os_ClrHome();

	/*Zero(g_inputBuffer, INPUT_SIZE);
	Zero(g_response, RESP_SIZE);
	Zero(buf, 5);*/

	sprintf(g_response, "Diameter: ");
	FloatToStringPretty(diam, 10, bigbuf);
	strcat(g_response, bigbuf);
	println(g_response, 0, 4);

	/*Zero(g_inputBuffer, INPUT_SIZE);
	Zero(g_response, RESP_SIZE);
	Zero(buf, 5);
	Zero(bigbuf, 20);*/

	sprintf(g_response, "Radius: ");
	FloatToStringPretty(radius, 5, buf);
	strcat(g_response, buf);
	println(g_response, 0, 0);

	Zero(g_inputBuffer, INPUT_SIZE);
	Zero(g_response, RESP_SIZE);
	Zero(buf, 5);

	sprintf(g_response, "Area: ");
	FloatToStringPretty(area, 10, bigbuf);
	strcat(g_response, bigbuf);
	println(g_response, 0, 2);

	sprintf(g_response, "Area (pi): ");
	FloatToStringPretty(DecimalToPi(area), 5, buf);
	strcat(g_response, buf);
	strcat(g_response, "pi");
	println(g_response, 0, 1);

	Zero(g_inputBuffer, INPUT_SIZE);
	Zero(g_response, RESP_SIZE);
	Zero(buf, 5);

	sprintf(g_response, "Circumference: ");
	FloatToStringPretty(circumf, 5, buf);
	strcat(g_response, buf);
	println(g_response, 0, 3);

	while (!os_GetCSC());
	os_ClrHome();
}

