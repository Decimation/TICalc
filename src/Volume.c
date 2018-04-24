//
// Created by Decimation on 4/23/2018.
//

#include "Volume.h"
#include "Formulas.h"


void vol_PrismCylinder()
{
	real_t B, h, V;
	char   buf[20];

	io_println(vol_PrismCylinderF, 0, 2);

	io_println("B?", 0, 1);
	B = io_ReadReal();
	os_ClrHome();

	io_println("h?", 0, 1);
	h = io_ReadReal();
	os_ClrHome();

	V = os_RealMul(&B, &h);

	os_RealToStr(buf, &V, 0, 0, 6);
	sprintf(g_response, "V = %s", buf);
	io_println(g_response, 0, 1);
}

void vol_Cube()
{
	real_t       a, V;
	const real_t real3 = os_Int24ToReal(3);
	char         buf[20];

	io_println(vol_CubeF, 0, 2);

	io_println("a?", 0, 1);
	a = io_ReadReal();
	os_ClrHome();


	V = os_RealPow(&a, &real3);

	os_RealToStr(buf, &V, 0, 0, 6);
	sprintf(g_response, "V = %s", buf);
	io_println(g_response, 0, 1);
}

void vol_PyramidCone()
{
	real_t       B, h, V;
	char         buf[20];
	const real_t realthird = os_FloatToReal(1 / 3);

	io_println(vol_PyramidConeF, 0, 2);

	io_println("B?", 0, 1);
	B = io_ReadReal();
	os_ClrHome();

	io_println("h?", 0, 1);
	h = io_ReadReal();
	os_ClrHome();

	V = os_RealMul(&B, &h);
	V = os_RealMul(&V, &realthird);

	os_RealToStr(buf, &V, 0, 0, 6);
	sprintf(g_response, "V = %s", buf);
	io_println(g_response, 0, 1);
}
