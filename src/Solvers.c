//
// Created by Decimation on 4/8/2018.
//

#include "Solvers.h"
#include "Simplifiers.h"
#include "Shapes.h"

void solve_Square()
{
	square_t sq;
	real_t real2 = os_Int24ToReal(2);
	real_t real4 = os_Int24ToReal(4);
	real_t sqrt2 = os_FloatToReal(sqrt(2));
	int      i;
	char     bigbuf[20];
	real_t    given = io_ReadReal();
	Zero(g_inputBuffer, INPUT_SIZE);
	io_ClearFirstLine();
	io_println("What was this data?", 0, 1);
	io_println("1:Side", 0, 2);
	io_println("2:Perimeter", 0, 3);
	io_println("3:Area", 0, 4);
	io_println("4:Diagonal", 0, 5);
	io_println("5:Diagonal area", 0, 6);
	i = io_ReadInt();

	if (i == 1)
	{
		sq.side          = given;
		//sq.area          = pow(sq.side, 2);
		sq.area = os_RealPow(&sq.side, &real2);
		//sq.perimeter     = sq.side * 4;
		sq.perimeter = os_RealMul(&sq.side, &real4);
		//sq.diagonal      = sq.side * sqrt(2);
		sq.diagonal = os_RealMul(&sq.side, &sqrt2);
		//sq.diagonal_area = sq.area / 2;
		sq.diagonal_area = os_RealDiv(&sq.area, &real2);
	}

	if (i == 2)
	{
		sq.perimeter     = given;
		//sq.side          = sq.perimeter / 4;
		sq.side = os_RealDiv(&sq.perimeter, &real4);
		//sq.area          = pow(sq.side, 2);
		sq.area = os_RealPow(&sq.side, &real2);
		//sq.diagonal      = sq.side * sqrt(2);
		sq.diagonal = os_RealMul(&sq.side, &sqrt2);
		//sq.diagonal_area = sq.area / 2;
		sq.diagonal_area = os_RealDiv(&sq.area, &real2);
	}

	if (i == 3)
	{
		sq.area          = given;
		//sq.side          = sqrt(sq.area);
		sq.side = os_RealSqrt(&sq.area);
		//sq.perimeter     = sq.side * 4;
		sq.perimeter = os_RealMul(&sq.side, &real4);
		//sq.diagonal      = sq.side * sqrt(2);
		sq.diagonal = os_RealMul(&sq.side, &sqrt2);
		//sq.diagonal_area = sq.area / 2;
		sq.diagonal_area = os_RealDiv(&sq.area, &real2);
	}

	if (i == 4)
	{
		sq.diagonal      = given;
		//sq.side          = sq.diagonal / sqrt(2);
		sq.side = os_RealDiv(&sq.diagonal, &sqrt2);
		//sq.perimeter     = sq.side * 4;
		sq.perimeter = os_RealMul(&sq.side, &real4);
		//sq.area          = pow(sq.side, 2);
		sq.area = os_RealPow(&sq.side, &real2);
		//sq.diagonal_area = sq.area / 2;
		sq.diagonal_area = os_RealDiv(&sq.area, &real2);
	}

	if (i == 5)
	{
		sq.diagonal_area = given;
		//sq.area          = sq.diagonal_area * 2;
		sq.area = os_RealMul(&sq.diagonal_area, &real2);
		//sq.side          = sqrt(sq.area);
		sq.side = os_RealSqrt(&sq.area);
		//sq.perimeter     = sq.side * 4;
		sq.perimeter = os_RealMul(&sq.side, &real4);
		//sq.diagonal      = sq.side * sqrt(2);
		sq.diagonal = os_RealMul(&sq.side, &sqrt2);
	}

	os_ClrHome();
	autoRound_Square(&sq);

	sprintf(g_response, "Side: ");
	//FloatToStringPretty(sq.side, 10, bigbuf);
	os_RealToStr(bigbuf, &sq.side, 0, 0, -1);
	strcat(g_response, bigbuf);
	io_println(g_response, 0, 1);

	sprintf(g_response, "Area: ");
	//FloatToStringPretty(sq.area, 10, bigbuf);
	os_RealToStr(bigbuf, &sq.area, 0, 0, -1);
	strcat(g_response, bigbuf);
	io_println(g_response, 0, 2);

	sprintf(g_response, "Perimeter: ");
	//FloatToStringPretty(sq.perimeter, 10, bigbuf);
	os_RealToStr(bigbuf, &sq.perimeter, 0, 0, -1);
	strcat(g_response, bigbuf);
	io_println(g_response, 0, 3);

	sprintf(g_response, "Diagonal: ");
	//FloatToStringPretty(sq.diagonal, 10, bigbuf);
	os_RealToStr(bigbuf, &sq.diagonal, 0, 0, -1);
	strcat(g_response, bigbuf);
	io_println(g_response, 0, 4);

	sprintf(g_response, "Diagonal area: ");
	//FloatToStringPretty(sq.diagonal_area, 10, bigbuf);
	os_RealToStr(bigbuf, &sq.diagonal_area, 0, 0, -1);
	strcat(g_response, bigbuf);
	io_println(g_response, 0, 5);
}

void solve_Circle()
{
	char     buf[5];
	char     bigbuf[20];
	int      i;
	circle_t circle;
	real_t tmp;
	const real_t real2 = os_Int24ToReal(2);
	const real_t realpi = os_FloatToReal(PI);
	real_t    given = io_ReadReal();
	float f;
	Zero(g_inputBuffer, INPUT_SIZE);
	io_ClearFirstLine();
	io_println("What was this data?", 0, 1);
	io_println("1:Radius", 0, 2);
	io_println("2:Area", 0, 3);
	io_println("3:Circumference", 0, 4);
	io_println("4:Diameter", 0, 5);
	i = io_ReadInt();

	if (i == 1)
	{
		circle.radius        = given;
		//circle.area          = PI * (float) pow(circle.radius, 2);
		tmp = os_RealPow(&circle.radius, &real2);
		circle.area = os_RealMul(&realpi, &tmp);
		circle.diameter = os_RealMul(&circle.radius, &real2);
		//circle.diameter      = circle.radius * 2;
		//circle.circumference = PI * circle.diameter;
		circle.circumference = os_RealMul(&realpi, &circle.diameter);
	}

	if (i == 2)
	{
		circle.area          = given;
		//tmp = os_RealSqrt(&circle.area);
		//circle.radius        = (float) sqrt(circle.area) / PI;
		//circle.radius = os_FloatToReal(sqrt(os_RealToFloat(&circle.area)) / PI);
		//circle.radius = os_RealDiv(&tmp, &realpi);
		//circle.diameter      = circle.radius * 2;
		tmp = os_RealDiv(&circle.area, &realpi);
		circle.radius = os_RealSqrt(&tmp);
		circle.diameter = os_RealMul(&circle.radius, &real2);
		//circle.circumference = PI * circle.diameter;
		circle.circumference = os_RealMul(&realpi, &circle.diameter);
	}

	if (i == 3)
	{
		circle.circumference = given;
		//circle.diameter      = circle.circumference / PI;
		circle.diameter = os_RealDiv(&circle.circumference, &realpi);
		//circle.radius        = circle.diameter / 2;
		circle.radius		= os_RealDiv(&circle.diameter, &real2);
		//circle.area          = PI * (float) pow(circle.radius, 2);
		tmp = os_RealPow(&circle.radius, &real2);
		circle.area = os_RealMul(&realpi, &tmp);
	}

	if (i == 4)
	{
		circle.diameter      = given;
		//circle.radius        = circle.diameter / 2;
		circle.radius = os_RealDiv(&circle.diameter, &real2);
		//circle.area          = PI * (float) pow(circle.radius, 2);
		tmp = os_RealPow(&circle.radius, &real2);
		circle.area = os_RealMul(&realpi, &tmp);
		//circle.circumference = PI * circle.diameter;
		circle.circumference = os_RealMul(&realpi, &circle.diameter);
	}

	os_ClrHome();

	io_print("Pulverizing memory...", 0, 0);
	autoRound_Circle(&circle);

	sprintf(g_response, "Diameter: ");
	//FloatToStringPretty(circle.diameter, 10, bigbuf);
	os_RealToStr(bigbuf, &circle.diameter,0,0,-1);
	strcat(g_response, bigbuf);
	io_println(g_response, 0, 5);

	sprintf(g_response, "Radius: ");
	//FloatToStringPretty(circle.radius, 5, buf);
	os_RealToStr(buf, &circle.radius,0,0,-1);
	strcat(g_response, buf);
	io_println(g_response, 0, 1);

	sprintf(g_response, "Area: ");
	//FloatToStringPretty(circle.area, 10, bigbuf);
	os_RealToStr(bigbuf, &circle.area,0,0,-1);
	strcat(g_response, bigbuf);
	io_println(g_response, 0, 2);

	sprintf(g_response, "Circumference: ");
	//FloatToStringPretty(circle.circumference, 5, buf);
	os_RealToStr(buf, &circle.circumference,0,0,-1);
	strcat(g_response, buf);
	io_println(g_response, 0, 4);

	sprintf(g_response, "Area (pi): ");
	//FloatToStringPretty(DecimalToPi(os_RealToFloat(&circle.area)), 5, bigbuf);
	f = DecimalToPi(os_RealToFloat(&circle.area));
	tmp = os_FloatToReal(f);
	os_RealToStr(bigbuf, &tmp,0,0,-1);
	strcat(g_response, bigbuf);
	io_println(g_response, 0, 3);

	io_ClearFirstLine();
	io_print("Memory pulverized", 0, 0);
}

void solve_Sphere()
{
	int      i;
	char     bigbuf[20];
	sphere_t sp;
	float f;
	real_t    given = io_ReadReal();
	const real_t real2 = os_Int24ToReal(2);
	const real_t real4 = os_Int24ToReal(4);
	real_t realpi = os_FloatToReal(PI);
	real_t tmp,tmp2,exp;
	Zero(g_inputBuffer, INPUT_SIZE);
	io_ClearFirstLine();
	io_println("What was this data?", 0, 1);
	io_println("1:Radius", 0, 2);
	io_println("2:Surface area", 0, 3);
	io_println("3:Volume", 0, 4);
	io_println("4:Diameter", 0, 5);
	i = io_ReadInt();

	if (i == 1)
	{
		sp.radius       = given;
		//sp.diameter     = sp.radius * 2;
		sp.diameter = os_RealMul(&sp.radius, &real2);
		sp.surface_area = surfaceArea_Sphere(sp.radius);
		sp.volume       = volume_Sphere(sp.radius);
	}

	if (i == 2)
	{
		sp.surface_area = given;
		//sp.radius       = sqrt((sp.surface_area / (4 * PI)));
		tmp = os_RealMul(&real4, &realpi);
		tmp2 = os_RealDiv(&sp.surface_area, &tmp);
		sp.radius = os_RealSqrt(&tmp2);
		//sp.diameter     = sp.radius * 2;
		sp.diameter = os_RealMul(&sp.radius, &real2);
		sp.volume       = volume_Sphere(sp.radius);
	}

	if (i == 3)
	{
		sp.volume       = given;
		tmp = os_FloatToReal((4 / 3) * PI);
		tmp2 = os_RealDiv(&sp.volume, &tmp);
		exp = os_FloatToReal(1/3);
		sp.radius = os_RealPow(&tmp2, &exp);
		//sp.radius       = pow(sp.volume / ((4 / 3) * PI), 1 / 3);

		//sp.diameter     = sp.radius * 2;
		sp.diameter = os_RealMul(&sp.radius, &real2);
		sp.surface_area = surfaceArea_Sphere(sp.radius);
	}

	if (i == 4)
	{
		sp.diameter     = given;
		//sp.radius       = sp.diameter / 2;
		sp.radius = os_RealDiv(&sp.diameter, &real2);
		sp.surface_area = surfaceArea_Sphere(sp.radius);
		sp.volume       = volume_Sphere(sp.radius);
	}

	os_ClrHome();
	io_print("Crunching floats...", 0, 0);
	autoRound_Sphere(&sp);

	sprintf(g_response, "Radius: ");
	//FloatToStringPretty(sp.radius, 10, bigbuf);
	os_RealToStr(bigbuf, &sp.radius,0,0,-1);
	strcat(g_response, bigbuf);
	io_println(g_response, 0, 1);

	sprintf(g_response, "Diameter: ");
	//FloatToStringPretty(sp.diameter, 10, bigbuf);
	os_RealToStr(bigbuf, &sp.diameter,0,0,-1);
	strcat(g_response, bigbuf);
	io_println(g_response, 0, 2);

	sprintf(g_response, "Volume: ");
	//FloatToStringPretty(sp.volume, 10, bigbuf);
	os_RealToStr(bigbuf, &sp.volume,0,0,-1);
	strcat(g_response, bigbuf);
	io_println(g_response, 0, 3);

	sprintf(g_response, "Surface area: ");
	//FloatToStringPretty(sp.surface_area, 10, bigbuf);
	os_RealToStr(bigbuf, &sp.surface_area,0,0,-1);
	strcat(g_response, bigbuf);
	io_println(g_response, 0, 5);

	sprintf(g_response, "Volume (pi): ");
	//FloatToStringPretty(DecimalToPi(os_RealToFloat(&sp.volume)), 10, bigbuf);
	f = DecimalToPi(os_RealToFloat(&sp.volume));
	tmp = os_FloatToReal(f);
	os_RealToStr(bigbuf, &tmp,0,0,-1);
	strcat(g_response, bigbuf);
	io_println(g_response, 0, 4);

	sprintf(g_response, "Surface area (pi): ");
	//FloatToStringPretty(DecimalToPi(os_RealToFloat(&sp.surface_area)), 10, bigbuf);
	f = DecimalToPi(os_RealToFloat(&sp.surface_area));
	tmp = os_FloatToReal(f);
	os_RealToStr(bigbuf, &tmp,0,0,-1);
	strcat(g_response, bigbuf);
	io_println(g_response, 0, 6);

	io_ClearFirstLine();
	io_print("Floats crunched", 0, 0);
}