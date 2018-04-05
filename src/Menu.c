//
// Created by Decimation on 4/4/2018.
//

#include "Menu.h"
#include "MathLib.h"
#include "Main.h"

int menu_Main()
{
	int i;
	os_ClrHome();
	println(" ] Rip and tear", 0, 0);
	println("1:Area", 0, 1);
	println("2:Surface area", 0, 2);
	println("3:Volume", 0, 3);
	println("4:Formulas", 0, 4);
	println("5:Polygons", 0, 5);
	println("6:Simplifiers", 0, 6);
	println("7:More", 0, 7);
	println("8:Exit", 0, 8);
	println("", 0, 9);

	os_SetCursorPos(0,9);
	i = ReadInt();
	sprintf(g_response, "] > %d <", i);
	print(g_response, 0, 9);

	if (i == 8) exit(0);
	return i;
}

void menu_Area() {
	int i;
	os_ClrHome();

	println(" ] Area",0,0);
	println("1:Circle",0,1);
	println("2:Square",0,2);
	println("3:Rect/rhombus/parallelo",0,3);
	println("4:Polygon",0,4);
	println("5:Triangle",0,5);
	println("6:Trapezoid",0,6);
	println("7:Back",0,7);

	i = ReadInt();
	sprintf(g_response, "] > %d <", i);
	print(g_response, 0, 9);

	if (i == 1) {
		os_ClrHome();
		solve_Circle();
		while (!os_GetCSC());
		menu_More();
	}

	if (i == 2) {
		os_ClrHome();

		while (!os_GetCSC());
		menu_More();
	}

	if (i == 3) {
		os_ClrHome();

		while (!os_GetCSC());
		menu_More();
	}

	if (i == 4) {
		os_ClrHome();

		while (!os_GetCSC());
		menu_More();
	}

	if (i == 5) {
		os_ClrHome();

		while (!os_GetCSC());
		menu_More();
	}

	if (i == 6) {
		os_ClrHome();

		while (!os_GetCSC());
		menu_More();
	}

	if (i == 7) {
		os_ClrHome();

		while (!os_GetCSC());
		menu_More();
	}

	if (i == 7) main();


	//while (!os_GetCSC());
	main();
}

void menu_More() {
	int i;
	os_ClrHome();

	println(" ] More",0,0);
	println("1:Primality checker",0,1);
	println("2:Josephus",0,2);
	println("3:Back",0,3);

	i = ReadInt();
	sprintf(g_response, "] > %d <", i);
	print(g_response, 0, 9);

	if (i == 1) {
		os_ClrHome();
		sprintf(g_response, "= %s", IsPrime(ReadInt()) ? "Prime" : "Not prime");
		print(g_response, 0,1);
		while (!os_GetCSC());
		menu_More();
	}

	if (i == 2) {
		os_ClrHome();
		sprintf(g_response, "Safe position = %d", GetSafePosition(ReadInt()));
		print(g_response, 0,1);
		while (!os_GetCSC());
		menu_More();
	}

	if (i == 3) main();

	//while (!os_GetCSC());
	main();
}

void menu_Simplifiers() {
	int i;
	float x;
	os_ClrHome();

	println("Simplifiers",0,0);
	println("1:Decimal to root",0,1);
	println("2:Decimal to pi",0,2);
	println("3:Back",0,3);

	i = ReadInt();
	sprintf(g_response, "] > %d <", i);
	print(g_response, 0, 9);

	if (i == 1)
	{
		os_ClrHome();
		x = DecimalToRoot(ReadFloat());
		sprintf(g_response, "= sqrt(%d)", (int) x);
		print(g_response, 0,1);
		while (!os_GetCSC());
		menu_Simplifiers();
	}

	if (i == 2) {
		os_ClrHome();
		x = DecimalToPi(ReadFloat());
		sprintf(g_response, "= %dpi", (int) x);
		print(g_response, 0,1);
		while (!os_GetCSC());
		menu_Simplifiers();
	}

	if (i == 3) main();

	//while (!os_GetCSC());
	main();
}