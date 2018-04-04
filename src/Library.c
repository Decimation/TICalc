/* Keep these headers */

#include <math.h>
#include "C:\CEdev\include\stddef.h"
#include "C:\CEdev\include\stdbool.h"
#include "C:\CEdev\include\tice.h"
#include "C:\CEdev\include\fileioc.h"
#include "C:\CEdev\include\stdint.h"
#include "Library.h"
#include "IO.h"



/**
 * THESE MUST BE GLOBAL OR ELSE EXITING
 * THE ENTRY POINT WILL CAUSE AN NMI RESET
 */
char    g_response[RESP_SIZE];
char    g_inputBuffer[INPUT_SIZE];
//int24_t g_value;

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
