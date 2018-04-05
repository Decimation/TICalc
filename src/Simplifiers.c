//
// Created by Decimation on 4/3/2018.
//

#include "Simplifiers.h"
#include "MathLib.h"


static const float Step = 0.1;
float DecimalToRoot(float d)
{
	float x = 0;
	while (sqrt(x) != d)
	{
		x += Step;
		if (sqrt(x) >= d)
			return (float) RoundIEEE754(x);
	}
	return x;
}



// TODO
float DecimalToPi(float f) {
	float x = 0;

	while (x * PI != f)
	{
		x += Step;
		if (x * PI > f)
			return (float) RoundIEEE754(x);
	}
	return x;
}