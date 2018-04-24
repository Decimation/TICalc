//
// Created by Decimation on 4/3/2018.
//


#include "MathLib.h"
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

real_t ArcLength(real_t M, real_t r) {
	// L = (M / 360) * (2(pi)r)
	real_t buf;
	const real_t real360 = os_Int24ToReal(360);
	const real_t real2 = os_Int24ToReal(2);
	const real_t realpi = os_FloatToReal(PI);
	M = os_RealDiv(&M, &real360);
	buf = os_RealMul(&real2, &realpi);
	buf = os_RealMul(&buf, &r);
	return os_RealMul(&M, &buf);
}
void SimplifyRadicalStrFromDecimal(real_t decimal, char* out)
{
	int24_t simp[2];
	SimplifyRadical((int) DecimalToRoot(os_RealToFloat(&decimal)), simp);
	sprintf(out, "%dsqrt(%d)", simp[0], simp[1]);
}

void SimplifyRadicalStr(int24_t insideRoot, char* out)
{
	int24_t simp[2];
	SimplifyRadical(insideRoot, simp);
	sprintf(out, "%dsqrt(%d)", simp[0], simp[1]);
}

void SimplifyRadical(int24_t insideRoot, int24_t out[2])
{
	int outside_root = 1;
	int d            = 2;
	while (d * d <= insideRoot)
	{
		if (insideRoot % (d * d) == 0)
		{
			insideRoot /= (d * d);
			outside_root *= d;
		}

		else
			d++;
	}
	out[0] = outside_root;
	out[1] = insideRoot;
}

real_t volume_Sphere(real_t radius)
{
	const real_t real3    = os_Int24ToReal(3);
	real_t       cub      = os_RealPow(&radius, &real3);
	real_t       coef     = os_FloatToReal(4.0 / 3);
	const real_t realpi   = os_FloatToReal(PI);
	real_t       leftSide = os_RealMul(&coef, &realpi);
	return os_RealMul(&leftSide, &cub);
	//return (4.0 / 3) * (PI) * radius * radius * radius;
}


real_t surfaceArea_Sphere(real_t radius)
{
	const real_t realpi    = os_FloatToReal(PI);
	const real_t real4     = os_Int24ToReal(4);
	const real_t real2     = os_Int24ToReal(2);
	real_t       leftSide  = os_RealMul(&real4, &realpi);
	real_t       rightSide = os_RealPow(&radius, &real2);
	return os_RealMul(&leftSide, &rightSide);
	//return 4 * PI * (float) pow(radius, 2);
}



