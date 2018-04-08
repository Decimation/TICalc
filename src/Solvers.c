//
// Created by Decimation on 4/8/2018.
//

#include "Solvers.h"
#include "Simplifiers.h"

void solve_Square()
{
	square_t sq;
	int      i;
	char     bigbuf[20];
	float    given = ReadFloat();
	println("What was this data?", 0, 1);
	println("1:Side", 0, 2);
	println("2:Perimeter", 0, 3);
	println("3:Area", 0, 4);
	println("4:Diagonal", 0, 5);
	println("5:Diagonal area", 0, 6);
	i = ReadInt();

	if (i == 1)
	{
		sq.side          = given;
		sq.area          = pow(sq.side, 2);
		sq.perimeter     = sq.side * 4;
		sq.diagonal      = sq.side * sqrt(2);
		sq.diagonal_area = sq.area / 2;
	}

	if (i == 2)
	{
		sq.perimeter     = given;
		sq.side          = sq.perimeter / 4;
		sq.area          = pow(sq.side, 2);
		sq.diagonal      = sq.side * sqrt(2);
		sq.diagonal_area = sq.area / 2;
	}

	if (i == 3)
	{
		sq.area          = given;
		sq.side          = sqrt(sq.area);
		sq.perimeter     = sq.side * 4;
		sq.diagonal      = sq.side * sqrt(2);
		sq.diagonal_area = sq.area / 2;
	}

	if (i == 4)
	{
		sq.diagonal      = given;
		sq.side          = sq.diagonal / sqrt(2);
		sq.perimeter     = sq.side * 4;
		sq.area          = pow(sq.side, 2);
		sq.diagonal_area = sq.area / 2;
	}

	if (i == 5)
	{
		sq.diagonal_area = given;
		sq.area          = sq.diagonal_area * 2;
		sq.side          = sqrt(sq.area);
		sq.perimeter     = sq.side * 4;
		sq.diagonal      = sq.side * sqrt(2);
	}

	os_ClrHome();
	autoRound_Square(&sq);

	sprintf(g_response, "Side: ");
	FloatToStringPretty(sq.side, 10, bigbuf);
	strcat(g_response, bigbuf);
	println(g_response, 0, 1);

	sprintf(g_response, "Area: ");
	FloatToStringPretty(sq.area, 10, bigbuf);
	strcat(g_response, bigbuf);
	println(g_response, 0, 2);

	sprintf(g_response, "Perimeter: ");
	FloatToStringPretty(sq.perimeter, 10, bigbuf);
	strcat(g_response, bigbuf);
	println(g_response, 0, 3);

	sprintf(g_response, "Diagonal: ");
	FloatToStringPretty(sq.diagonal, 10, bigbuf);
	strcat(g_response, bigbuf);
	println(g_response, 0, 4);

	sprintf(g_response, "Diagonal area: ");
	FloatToStringPretty(sq.diagonal_area, 10, bigbuf);
	strcat(g_response, bigbuf);
	println(g_response, 0, 5);
}

void solve_Circle()
{
	char     buf[5];
	char     bigbuf[20];
	int      i;
	circle_t circle;
	float    given = ReadFloat();
	Zero(g_inputBuffer, INPUT_SIZE);
	ClearFirstLine();
	println("What was this data?", 0, 1);
	println("1:Radius", 0, 2);
	println("2:Area", 0, 3);
	println("3:Circumference", 0, 4);
	println("4:Diameter", 0, 5);
	i = ReadInt();

	if (i == 1)
	{
		circle.radius        = given;
		circle.area          = PI * (float) pow(circle.radius, 2);
		circle.diameter      = circle.radius * 2;
		circle.circumference = PI * circle.diameter;
	}

	if (i == 2)
	{
		circle.area          = given;
		circle.radius        = (float) sqrt(circle.area) / PI;
		circle.diameter      = circle.radius * 2;
		circle.circumference = PI * circle.diameter;
	}

	if (i == 3)
	{
		circle.circumference = given;
		circle.diameter      = circle.circumference / PI;
		circle.radius        = circle.diameter / 2;
		circle.area          = PI * (float) pow(circle.radius, 2);
	}

	if (i == 4)
	{
		circle.diameter      = given;
		circle.radius        = circle.diameter / 2;
		circle.area          = PI * (float) pow(circle.radius, 2);
		circle.circumference = PI * circle.diameter;
	}

	os_ClrHome();

	/*Zero(g_inputBuffer, INPUT_SIZE);
	Zero(g_response, RESP_SIZE);
	Zero(buf, 5);*/

	print("Pulverizing memory...", 0, 0);
	autoRound_Circle(&circle);

	sprintf(g_response, "Diameter: ");
	FloatToStringPretty(circle.diameter, 10, bigbuf);
	strcat(g_response, bigbuf);
	println(g_response, 0, 4);

	/*Zero(g_inputBuffer, INPUT_SIZE);
	Zero(g_response, RESP_SIZE);
	Zero(buf, 5);
	Zero(bigbuf, 20);*/

	sprintf(g_response, "Radius: ");
	FloatToStringPretty(circle.radius, 5, buf);
	strcat(g_response, buf);
	println(g_response, 0, 0);

	sprintf(g_response, "Area: ");
	FloatToStringPretty(circle.area, 10, bigbuf);
	strcat(g_response, bigbuf);
	println(g_response, 0, 2);

	sprintf(g_response, "Circumference: ");
	FloatToStringPretty(circle.circumference, 5, buf);
	strcat(g_response, buf);
	println(g_response, 0, 3);

	sprintf(g_response, "Area (pi): ");
	FloatToStringPretty(DecimalToPi(circle.area), 5, buf);
	strcat(g_response, buf);
	strcat(g_response, "pi");
	println(g_response, 0, 1);

	ClearFirstLine();
	print("Memory pulverized", 0, 0);
	while (!os_GetCSC());
	os_ClrHome();
}

void solve_Sphere()
{
	int      i;
	char     bigbuf[20];
	sphere_t sp;
	float    given = ReadFloat();
	Zero(g_inputBuffer, INPUT_SIZE);
	ClearFirstLine();
	println("What was this data?", 0, 1);
	println("1:Radius", 0, 2);
	println("2:Surface area", 0, 3);
	println("3:Volume", 0, 4);
	println("4:Diameter", 0, 5);
	i = ReadInt();

	if (i == 1)
	{
		sp.radius       = given;
		sp.diameter     = sp.radius * 2;
		sp.surface_area = surfaceArea_Sphere(sp.radius);
		sp.volume       = volume_Sphere(sp.radius);
	}

	if (i == 2)
	{
		sp.surface_area = given;
		sp.radius       = sqrt((sp.surface_area / (4 * PI)));
		sp.diameter     = sp.radius * 2;
		sp.volume       = volume_Sphere(sp.radius);
	}

	if (i == 3)
	{
		sp.volume       = given;
		sp.radius       = pow(sp.volume / ((4 / 3) * PI), 1 / 3);
		sp.diameter     = sp.radius * 2;
		sp.surface_area = surfaceArea_Sphere(sp.radius);
	}

	if (i == 4)
	{
		sp.diameter     = given;
		sp.radius       = sp.diameter / 2;
		sp.surface_area = surfaceArea_Sphere(sp.radius);
		sp.volume       = volume_Sphere(sp.radius);
	}

	os_ClrHome();
	print("Crunching floats...", 0, 0);
	autoRound_Sphere(&sp);

	sprintf(g_response, "Radius: ");
	FloatToStringPretty(sp.radius, 10, bigbuf);
	strcat(g_response, bigbuf);
	println(g_response, 0, 1);

	sprintf(g_response, "Diameter: ");
	FloatToStringPretty(sp.diameter, 10, bigbuf);
	strcat(g_response, bigbuf);
	println(g_response, 0, 2);

	sprintf(g_response, "Volume: ");
	FloatToStringPretty(sp.volume, 10, bigbuf);
	strcat(g_response, bigbuf);
	println(g_response, 0, 3);

	sprintf(g_response, "Surface area: ");
	FloatToStringPretty(sp.surface_area, 10, bigbuf);
	strcat(g_response, bigbuf);
	println(g_response, 0, 5);

	sprintf(g_response, "Volume (pi): ");
	FloatToStringPretty(DecimalToPi(sp.volume), 10, bigbuf);
	strcat(g_response, bigbuf);
	println(g_response, 0, 4);

	sprintf(g_response, "Surface area (pi): ");
	FloatToStringPretty(DecimalToPi(sp.surface_area), 10, bigbuf);
	strcat(g_response, bigbuf);
	println(g_response, 0, 6);

	ClearFirstLine();
	print("Floats crunched", 0, 0);
	while (!os_GetCSC());
	os_ClrHome();
}