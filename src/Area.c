//
// Created by Decimation on 4/23/2018.
//

#include "Area.h"



void area_Rectangle()
{
	real_t l, w, A;
	char   buf[20];
	io_println(area_RectangleF, 0, 2);

	io_println("l?", 0, 1);
	l = io_ReadReal();
	os_ClrHome();
	io_println("w?", 0, 1);
	w = io_ReadReal();

	os_ClrHome();
	A = os_RealMul(&l, &w);
	os_RealToStr(buf, &A, 0, 0, 6);
	sprintf(g_response, "A = %s", buf);
	io_println(g_response, 0, 1);
}

void area_Polygon()
{
	real_t       a, p, A;
	const real_t real2 = os_Int24ToReal(2);
	char         buf[20];
	io_println(area_RegularPolyF, 0, 2);

	io_println("a?", 0, 1);
	a = io_ReadReal();
	os_ClrHome();
	io_println("p?", 0, 1);
	p = io_ReadReal();

	os_ClrHome();
	A = os_RealMul(&a, &p);
	A = os_RealDiv(&A, &real2);
	os_RealToStr(buf, &A, 0, 0, 6);
	sprintf(g_response, "A = %s", buf);
	io_println(g_response, 0, 1);
}

void area_Triangle()
{
	real_t       b, h, A;
	const real_t real2 = os_Int24ToReal(2);
	char         buf[20];
	io_println(area_TriangleF, 0, 2);

	io_println("b?", 0, 1);
	b = io_ReadReal();
	os_ClrHome();
	io_println("h?", 0, 1);
	h = io_ReadReal();
	os_ClrHome();

	A = os_RealMul(&b, &h);
	A = os_RealDiv(&A, &real2);
	os_RealToStr(buf, &A, 0, 0, 6);
	sprintf(g_response, "A = %s", buf);
	io_println(g_response, 0, 1);
}

void area_Trapezoid()
{
	real_t       b1, b2, h, A, rbuf, rbuf2;
	const real_t real2 = os_Int24ToReal(2);
	char         buf[20];
	io_println(area_TrapezoidF, 0, 2);

	io_println("h?", 0, 1);
	h = io_ReadReal();
	os_ClrHome();

	io_println("b1?", 0, 1);
	b1 = io_ReadReal();
	os_ClrHome();

	io_println("b2?", 0, 1);
	b2 = io_ReadReal();
	os_ClrHome();

	rbuf  = os_RealMul(&h, &real2);
	rbuf2 = os_RealAdd(&b1, &b2);
	A     = os_RealMul(&rbuf, &rbuf2);
	os_RealToStr(buf, &A, 0, 0, 6);
	sprintf(g_response, "A = %s", buf);
	io_println(g_response, 0, 1);
}

void area_Rhombus()
{
	real_t       d1, d2, A, rbuf;
	const real_t real2 = os_Int24ToReal(2);
	char         buf[20];
	io_println(area_KiteRhomF, 0, 2);

	io_println("d1?", 0, 1);
	d1 = io_ReadReal();
	os_ClrHome();

	io_println("d2?", 0, 1);
	d2 = io_ReadReal();
	os_ClrHome();

	rbuf = os_RealMul(&d1, &d2);
	A    = os_RealDiv(&rbuf, &real2);
	os_RealToStr(buf, &A, 0, 0, 6);
	sprintf(g_response, "A = %s", buf);
	io_println(g_response, 0, 1);
}

void area_Parallelogram()
{
	real_t b, h, A;
	char   buf[20];
	io_println(area_ParallelogramF, 0, 2);

	io_println("b?", 0, 1);
	b = io_ReadReal();
	os_ClrHome();
	io_println("h?", 0, 1);
	h = io_ReadReal();

	os_ClrHome();
	A = os_RealMul(&b, &h);
	os_RealToStr(buf, &A, 0, 0, 6);
	sprintf(g_response, "A = %s", buf);
	io_println(g_response, 0, 1);
}

void area_Square()
{
	real_t       s, A;
	const real_t real2 = os_Int24ToReal(2);
	char         buf[20];
	io_println(area_SquareF, 0, 2);

	io_println("s?", 0, 1);
	s = io_ReadReal();

	os_ClrHome();
	A = os_RealPow(&s, &real2);
	os_RealToStr(buf, &A, 0, 0, 6);
	sprintf(g_response, "A = %s", buf);
	io_println(g_response, 0, 1);
}