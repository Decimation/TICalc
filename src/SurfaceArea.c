//
// Created by Decimation on 4/23/2018.
//

#include "SurfaceArea.h"




void sa_PrismCylinder()
{
	real_t       p, h, B, S;
	char         buf[20];
	const real_t real2 = os_Int24ToReal(2);

	io_println(sa_PrismCylinderF, 0, 2);

	io_println("p?", 0, 1);
	p = io_ReadReal();
	os_ClrHome();

	io_println("h?", 0, 1);
	h = io_ReadReal();
	os_ClrHome();

	io_println("B?", 0, 1);
	B = io_ReadReal();
	os_ClrHome();

	S = os_RealMul(&p, &h);
	B = os_RealMul(&B, &real2);
	S = os_RealAdd(&S, &B);

	os_RealToStr(buf, &S, 0, 0, 6);
	sprintf(g_response, "S = %s", buf);
	io_println(g_response, 0, 1);
}

void sa_Pyramid()
{
	real_t       p, l, B, S, tmp;
	char         buf[20];
	const real_t real2 = os_Int24ToReal(2);

	io_println(sa_PyramidF, 0, 2);

	io_println("p?", 0, 1);
	p = io_ReadReal();
	os_ClrHome();

	io_println("l?", 0, 1);
	l = io_ReadReal();
	os_ClrHome();

	io_println("B?", 0, 1);
	B = io_ReadReal();
	os_ClrHome();

	tmp = os_RealMul(&p, &l);
	tmp = os_RealDiv(&tmp, &real2);
	S   = os_RealAdd(&B, &tmp);

	os_RealToStr(buf, &S, 0, 0, 6);
	sprintf(g_response, "S = %s", buf);
	io_println(g_response, 0, 1);
}

void sa_Cone()
{
	real_t       r, l, S, rsq, tmp, rl;
	char         buf[20];
	const real_t realpi = os_FloatToReal(PI);

	io_println(sa_ConeF, 0, 2);

	io_println("r?", 0, 1);
	r = io_ReadReal();
	os_ClrHome();

	io_println("l?", 0, 1);
	l = io_ReadReal();
	os_ClrHome();

	rsq = os_RealMul(&r, &r);
	tmp = os_RealMul(&realpi, &rsq);

	rl = os_RealMul(&r, &l);
	rl = os_RealMul(&rl, &realpi);

	S = os_RealAdd(&tmp, &rl);

	os_RealToStr(buf, &S, 0, 0, 6);
	sprintf(g_response, "S = %s", buf);
	io_println(g_response, 0, 1);
}
