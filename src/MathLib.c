//
// Created by Decimation on 4/3/2018.
//


#include "MathLib.h"

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


/**
 * Fucking fucking FUCK stupid real_t list gay shit
 * @param x
 * @return
 */
list_t* Factors(int24_t x)
{
	int i;
	list_t* factors;
	unsigned int numberOfFactors = 0;
	for (i = 1; i <= x; i++)
	{
		if (x % i == 0)
		{

			numberOfFactors++;
		}
	}
	factors = ti_MallocList(numberOfFactors);

	for (i = 1; i <= x; i++)
	{
		if (x % i == 0)
		{
			factors->items[i - 1] = os_FloatToReal(i);
		}
	}

	factors->items[factors->dim - 1] = os_FloatToReal(x);
	return factors;

}

int24_t GetSafePosition(int24_t n)
{
	// find value of L for the equation
	int24_t valueOfL     = n - HighestOneBit(n);
	int24_t safePosition = 2 * valueOfL + 1;

	return safePosition;
}

const float PI = 3.141592654f;

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



