//
// Created by Decimation on 4/4/2018.
//

#include "Menu.h"
#include "MathLib.h"
#include "Main.h"
#include "Solvers.h"
#include "Sequences.h"
#include "Trigonometry.h"

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
	EchoInput(i);

	if (i == 8) {
		sys_GarbageCollect();
		exit(0);
	}
	return i;
}

void menu_Area()
{
	int i;
	os_ClrHome();

	io_println("Area", 0, 1);
	io_println("3:Rect/rhombus/parallelo", 0, 2);
	io_println("4:Polygon", 0, 3);
	io_println("5:Triangle", 0, 4);
	io_println("6:Trapezoid", 0, 5);
	io_println("7:Back", 0, 6);

	i = io_ReadInt();
	EchoInput(i);


	if (i == 7) main();


	//while (!os_GetCSC());
	main();
}

void menu_Trig()
{
	int i;
	os_ClrHome();

	io_println("Trigonometry", 0, 1);
	io_println("1:Solve right triangle", 0, 2);
	io_println("2:Solve 30/60/90", 0, 3);
	io_println("3:Solve 45/45/90", 0, 4);
	io_println("4:Back", 0, 5);

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

		while (!os_GetCSC());
		menu_Trig();
	}

	if (i == 3)
	{
		os_ClrHome();

		while (!os_GetCSC());
		menu_Trig();
	}

	if (i == 4)
	{
		menu_More();
	}
}

void menu_More()
{
	int i;
	int seq_len;
	real_t* seq_arr;

	os_ClrHome();

	io_println("More", 0, 1);
	io_println("1:Primality checker", 0, 2);
	io_println("2:Josephus", 0, 3);
	io_println("3:Trigonometry", 0, 4);
	io_println("4:Solvers", 0, 5);
	io_println("5:Sequence analyzer", 0, 6);
	io_println("6:Back", 0, 7);

	i = io_ReadInt();
	EchoInput(i);

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


	if (i == 5) {
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

	if (i == 6) main();

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
	EchoInput(i);

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
	EchoInput(i);

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