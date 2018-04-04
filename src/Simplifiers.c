//
// Created by Decimation on 4/3/2018.
//

#include "Simplifiers.h"

static const float Step = 0.1;
float DecimalToRoot(float d)
{
	float x = 0;
	while (sqrt(x) != d)
	{
		x += Step;
		if (sqrt(x) >= d)
			return ceil(x);
	}
	return x;
}

// TODO
void DecimalToPi(float f, char* out) {
	/*const double pi = acos(-1);
	float step;
	step = 0.1;


	while (step * pi != f)
	{
		step += 0.1;
		if (step * pi > f)
		{
			sprintf(out, "%f\140", step);
		}
	}
	out = "ERROR";*/
}