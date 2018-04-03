//
// Created by Decimation on 4/3/2018.
//

#ifndef TICALC_LIBRARY_H
#define TICALC_LIBRARY_H


#include <string.h>
#include <stdio.h>
#include <math.h>

/* Prepends t into s. Assumes s has enough space allocated
** for the combined string.
*/
void prepend(char* s, const char* t)
{
	size_t len = strlen(t);
	size_t i;

	memmove(s + len, s, strlen(s) + 1);

	for (i = 0; i < len; ++i)
	{
		s[i] = t[i];
	}
}

int indexOf(char* values, char find)
{
	int index;
	const char* ptr = strchr(values, find);

	index = ptr - values;
	return index;
}

char intToChar(int c)
{
	return c + '0';
}

int GetMantissa(float f)
{
	char fstr[20];
	char mstr[20];
	int  i;
	sprintf(fstr, "%f", f);

	i = 0;

	for (; fstr[indexOf(fstr, '.') + 1 + i] != '\0'; i++)
	{
		mstr[i] = fstr[indexOf(fstr, '.') + 1 + i];
	}
	return atoi(mstr);
}

/*
 *      Remove given section from string. Negative len means remove
 *      everything up to the end.
 */
int str_cut(char* str, int begin, int len)
{
	int l = strlen(str);

	if (len < 0) len         = l - begin;
	if (begin + len > l) len = l - begin;
	memmove(str + begin, str + begin + len, l - len + 1);

	return len;
}

float StringToFloat(char* in)
{
	in[indexOf(in, ':')] = '.';
	return atof(in);
}


#define MAX_PRECISION    (10)
static const double rounders[MAX_PRECISION + 1] =
{
		0.5,                // 0
		0.05,                // 1
		0.005,                // 2
		0.0005,                // 3
		0.00005,            // 4
		0.000005,            // 5
		0.0000005,            // 6
		0.00000005,            // 7
		0.000000005,        // 8
		0.0000000005,        // 9
		0.00000000005        // 10
};

char* FloatToString(double f, char* buf, int precision)
{
	char* ptr = buf;
	char* p   = ptr;
	char* p1;
	char c;
	long intPart;

	// check precision bounds
	if (precision > MAX_PRECISION)
		precision = MAX_PRECISION;

	// sign stuff
	if (f < 0)
	{
		f = -f;
		*ptr++ = '-';
	}

	if (precision < 0)  // negative precision == automatic precision guess
	{
		if (f < 1.0) precision = 6;
		else if (f < 10.0) precision = 5;
		else if (f < 100.0) precision = 4;
		else if (f < 1000.0) precision = 3;
		else if (f < 10000.0) precision = 2;
		else if (f < 100000.0) precision = 1;
		else precision = 0;
	}

	// round value according the precision
	if (precision)
		f += rounders[precision];

	// integer part...
	intPart = f;
	f -= intPart;

	if (!intPart)
		*ptr++ = '0';
	else
	{
		// save start pointer
		p = ptr;

		// convert (reverse order)
		while (intPart)
		{
			*p++ = '0' + intPart % 10;
			intPart /= 10;
		}

		// save end pos
		p1 = p;

		// reverse result
		while (p > ptr)
		{
			c = *--p;
			*p     = *ptr;
			*ptr++ = c;
		}

		// restore end pos
		ptr = p1;
	}

	// decimal part
	if (precision)
	{
		// place decimal point
		*ptr++ = '.';

		// convert
		while (precision--)
		{
			f *= 10.0;
			c = f;
			*ptr++ = '0' + c;
			f -= c;
		}
	}

	// terminating zero
	*ptr = 0;

	return buf;
}

#endif //TICALC_LIBRARY_H
