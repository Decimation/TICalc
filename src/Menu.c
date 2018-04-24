//
// Created by Decimation on 4/4/2018.
//

#include "Formulas.h"
#include "Menu.h"
#include "MathLib.h"
#include "Main.h"
#include "Solvers.h"
#include "Sequences.h"
#include "Trigonometry.h"
#include "Area.h"
#include "RightTrig.h"
#include "SurfaceArea.h"
#include "Volume.h"


int menu_Main()
{
	int i;
	os_ClrHome();
	io_println("Rip and tear", 0, 1);
	io_println("1:Area", 0, 2);
	io_println("2:Surface area", 0, 3);
	io_println("3:Volume", 0, 4);
	io_println("4:Formulas", 0, 5);
	io_println("5:Polygons", 0, 6);
	io_println("6:Simplifiers", 0, 7);
	io_println("7:More", 0, 8);
	io_println("8:Exit", 0, 9);

	i = io_ReadInt();
	//EchoInput(i);

	if (i == 8)
	{
		sys_GarbageCollect();
		exit(0);
	}
	return i;
}

void menu_Polygons() {
	int i;
	real_t n, rbuf;

	const real_t real2 = os_Int24ToReal(2);
	const real_t real180 = os_Int24ToReal(180);
	const real_t real360 = os_Int24ToReal(360);
	os_ClrHome();


	io_println("Polygons", 0, 1);
	io_println("1:Sum of interior angles", 0, 2);
	io_println("2:Measure of 1 int. angle", 0, 3);
	io_println("3:Sum of exterior angles", 0, 4);
	io_println("4:Measure of 1 ext. angle", 0, 5);
	io_println("5:Back", 0, 6);
	i = io_ReadInt();

	if (i == 1) {
		os_ClrHome();
		io_println(geo_SumOfIntAnglesF, 0, 2);
		io_println("n?", 0, 1);
		n = io_ReadReal();
		os_ClrHome();
		n = os_RealSub(&n, &real2);
		rbuf = os_RealMul(&real180, &n);
		os_RealToStr(g_inputBuffer, &rbuf,0,0,6);
		sprintf(g_response, " = %s", g_inputBuffer);
		io_println(g_response,0,1);
		while (!os_GetCSC());
		menu_Polygons();
	}

	if (i == 2) {
		os_ClrHome();
		io_println(geo_MeasureOf1IntAngleF, 0, 2);
		io_println("n?", 0, 1);
		n = io_ReadReal();
		os_ClrHome();
		n = os_RealSub(&n, &real2);
		rbuf = os_RealMul(&real180, &n);
		rbuf = os_RealDiv(&rbuf, &real2);
		os_RealToStr(g_inputBuffer, &rbuf,0,0,6);
		sprintf(g_response, " = %s", g_inputBuffer);
		io_println(g_response,0,1);
		while (!os_GetCSC());
		menu_Polygons();
	}

	if (i == 3) {
		os_ClrHome();
		io_println("Sum of exterior angles = 360", 0, 1);
		while (!os_GetCSC());
		menu_Polygons();
	}

	if (i == 4) {
		os_ClrHome();
		io_println(geo_MeasureOf1ExtAngleF, 0, 2);
		io_println("n?", 0, 1);
		n = io_ReadReal();
		os_ClrHome();
		rbuf = os_RealDiv(&real360, &n);
		os_RealToStr(g_inputBuffer, &rbuf,0,0,6);
		sprintf(g_response, " = %s", g_inputBuffer);
		io_println(g_response,0,1);
		while (!os_GetCSC());
		menu_Polygons();
	}

	if (i == 5) main();
	main();
}

void menu_Volume()
{
	int i;
	os_ClrHome();

	io_println("Volume", 0, 1);
	io_println("1:Prism/Cylinder", 0, 2);
	io_println("2:Pyramid/Cone", 0, 3);
	io_println("3:Cube", 0, 4);
	io_println("4:Sphere", 0, 5);
	io_println("5:Back", 0, 6);
	i = io_ReadInt();

	if (i == 1)
	{
		os_ClrHome();
		vol_PrismCylinder();
		while (!os_GetCSC());
		menu_Volume();
	}

	if (i == 2)
	{
		os_ClrHome();
		vol_PyramidCone();
		while (!os_GetCSC());
		menu_Volume();
	}

	if (i == 3)
	{
		os_ClrHome();
		vol_Cube();
		while (!os_GetCSC());
		menu_Volume();
	}

	if (i == 4)
	{
		os_ClrHome();
		solve_Sphere(); // redirection
		while (!os_GetCSC());
		menu_Volume();
	}

	if (i == 5)
	{
		main();
	}
	main();
}

void menu_SurfaceArea()
{
	int i;
	os_ClrHome();

	io_println("Surface Area", 0, 1);
	io_println("1:Prism/Cylinder", 0, 2);
	io_println("2:Pyramid", 0, 3);
	io_println("3:Cone", 0, 4);
	io_println("4:Sphere", 0, 5);
	io_println("5:Back", 0, 6);

	i = io_ReadInt();

	if (i == 1)
	{
		os_ClrHome();
		sa_PrismCylinder();

		while (!os_GetCSC());
		menu_SurfaceArea();
	}

	if (i == 2)
	{
		os_ClrHome();
		sa_Pyramid();

		while (!os_GetCSC());
		menu_SurfaceArea();
	}

	if (i == 3)
	{
		os_ClrHome();
		sa_Cone();

		while (!os_GetCSC());
		menu_SurfaceArea();
	}

	if (i == 4)
	{
		os_ClrHome();
		solve_Sphere(); // redirection

		while (!os_GetCSC());
		menu_SurfaceArea();
	}

	if (i == 5)
	{
		main();
	}
	main();
}

void menu_Area()
{
	int i;
	os_ClrHome();

	io_println("Area", 0, 1);
	io_println("1:Rectangle", 0, 2);
	io_println("2:Polygon", 0, 3);
	io_println("3:Triangle", 0, 4);
	io_println("4:Trapezoid", 0, 5);
	io_println("5:Rhombus/Kite", 0, 6);
	io_println("6:Parallelogram", 0, 7);
	io_println("7:Square", 0, 8);
	io_println("8:Back", 0, 9);

	i = io_ReadInt();
	//EchoInput(i);

	if (i == 1)
	{
		os_ClrHome();
		area_Rectangle();

		while (!os_GetCSC());
		menu_Area();
	}

	if (i == 2)
	{
		os_ClrHome();
		area_Polygon();

		while (!os_GetCSC());
		menu_Area();
	}

	if (i == 3)
	{
		os_ClrHome();
		area_Triangle();

		while (!os_GetCSC());
		menu_Area();
	}

	if (i == 4)
	{
		os_ClrHome();
		area_Trapezoid();

		while (!os_GetCSC());
		menu_Area();
	}

	if (i == 5)
	{
		os_ClrHome();
		area_Rhombus();

		while (!os_GetCSC());
		menu_Area();
	}

	if (i == 6)
	{
		os_ClrHome();
		area_Parallelogram();

		while (!os_GetCSC());
		menu_Area();
	}

	if (i == 7)
	{
		os_ClrHome();
		area_Square();

		while (!os_GetCSC());
		menu_Area();
	}

	if (i == 8) main();

	//while (!os_GetCSC());
	main();

}

void menu_Trig()
{
	int i;
	os_ClrHome();

	io_println("Trigonometry", 0, 1);
	io_println("1:Solve non-right triangle", 0, 2);
	//io_println("2:Solve 30/60/90", 0, 3);
	//io_println("3:Solve 45/45/90", 0, 4);
	io_println("2:Solve right triangle", 0, 3);
	io_println("3:Back", 0, 4);
	i = io_ReadInt();

	if (i == 1)
	{
		os_ClrHome();
		trig_SolveTriangle();
		while (!os_GetCSC());
		menu_Trig();
	}

	if (i == 2)
	{
		os_ClrHome();
		trig_SolveRightTriangle();
		while (!os_GetCSC());
		menu_Trig();
	}


	if (i == 3)
	{
		//return;
		//menu_More();
		main();
	}
	main();
}

void menu_More()
{
	int i;
	int seq_len;
	real_t* seq_arr;

	real_t M, r, L;

	os_ClrHome();

	io_println("More", 0, 1);
	io_println("1:Primality checker", 0, 2);
	io_println("2:Josephus", 0, 3);
	io_println("3:Trigonometry", 0, 4);
	io_println("4:Solvers", 0, 5);
	io_println("5:Sequence analyzer", 0, 6);
	io_println("6:Arc length", 0, 7);
	io_println("7:Back", 0, 8);

	i = io_ReadInt();
	//EchoInput(i);

	if (i == 1)
	{
		os_ClrHome();
		sprintf(g_response, "= %s", IsPrime(io_ReadInt()) ? "Prime" : "Not prime");
		io_print(g_response, 0, 1);
		while (!os_GetCSC());
		menu_More();
	}

	if (i == 2)
	{
		os_ClrHome();
		sprintf(g_response, "Safe position = %d", GetSafePosition(io_ReadInt()));
		io_print(g_response, 0, 1);
		while (!os_GetCSC());
		menu_More();
	}

	if (i == 3)
	{
		os_ClrHome();
		menu_Trig();
		while (!os_GetCSC());
		menu_More();
	}

	if (i == 4)
	{
		os_ClrHome();
		menu_Solvers();
		while (!os_GetCSC());
		menu_More();
	}


	if (i == 5)
	{
		os_ClrHome();

		io_print("Length of sequence? ", 0, 1);

		seq_len = io_ReadInt();
		seq_arr = malloc(sizeof(real_t) * seq_len);


		os_ClrHome();
		io_ReadArray(seq_arr, seq_len);
		os_ClrHome();

		seq_IdentifySequence(seq_arr, seq_len);

		while (!os_GetCSC());
		menu_More();
		free(seq_arr);
	}

	if (i == 6) {
		os_ClrHome();

		io_print(geo_ArcLengthF, 0, 2);
		io_print("M?", 0, 1);
		M = io_ReadReal();
		os_ClrHome();
		io_print("r?", 0, 1);
		r = io_ReadReal();
		os_ClrHome();

		L = ArcLength(M, r);
		os_RealToStr(g_inputBuffer, &L, 0, 0, 6);
		sprintf(g_response, "L = %s", g_inputBuffer);
		io_println(g_response, 0, 1);
		while (!os_GetCSC());
		menu_More();
	}

	if (i == 7) main(); //menu_Main();//return;//main();

	//while (!os_GetCSC());
	main();
}

void menu_Solvers()
{
	int i;

	os_ClrHome();

	io_println("Solvers", 0, 1);
	io_println("1:Circle", 0, 2);
	io_println("2:Square", 0, 3);
	io_println("3:Sphere", 0, 4);
	io_println("4:Back", 0, 5);

	i = io_ReadInt();
	//EchoInput(i);

	if (i == 1)
	{
		os_ClrHome();
		solve_Circle();
		while (!os_GetCSC());
		menu_Solvers();
	}

	if (i == 2)
	{
		os_ClrHome();
		solve_Square();
		while (!os_GetCSC());
		menu_Solvers();
	}

	if (i == 3)
	{
		os_ClrHome();
		solve_Sphere();
		while (!os_GetCSC());
		menu_Solvers();
	}

	if (i == 4) main();

	//while (!os_GetCSC());
	main();
}

void menu_Simplifiers()
{
	int   i;
	float x;
	os_ClrHome();

	io_println("Simplifiers", 0, 1);
	io_println("1:Decimal to root", 0, 2);
	io_println("2:Decimal to pi", 0, 3);
	io_println("3:Back", 0, 4);

	i = io_ReadInt();
	//EchoInput(i);

	if (i == 1)
	{
		os_ClrHome();
		x = DecimalToRoot(io_ReadFloat());
		sprintf(g_response, "= sqrt(%d)", (int) x);
		io_print(g_response, 0, 1);
		while (!os_GetCSC());
		menu_Simplifiers();
	}

	if (i == 2)
	{
		os_ClrHome();
		x = DecimalToPi(io_ReadFloat());
		sprintf(g_response, "= %dpi", (int) x);
		io_print(g_response, 0, 1);
		while (!os_GetCSC());
		menu_Simplifiers();
	}

	if (i == 3) main();

	//while (!os_GetCSC());
	main();
}