//
// Created by Decimation on 4/3/2018.
//

#include "Simplifiers.h"

float DecimalToRoot(float d)
{
	float step;
	step = 0.1;

	while (sqrt(step) != d)
	{
		step += 0.1;
		if (sqrt(step) > d)
			return -1;
	}
	return step;
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