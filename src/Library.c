/* Keep these headers */

#include <math.h>
#include "C:\CEdev\include\stddef.h"
#include "C:\CEdev\include\stdbool.h"
#include "C:\CEdev\include\fileioc.h"
#include "Library.h"
#include "IO.h"


/**
 * THESE MUST BE GLOBAL OR ELSE EXITING
 * THE ENTRY POINT WILL CAUSE AN NMI RESET
 */
char g_response[RESP_SIZE];
char g_inputBuffer[INPUT_SIZE];
//int24_t g_value;

void EchoInput(int i)
{
	sprintf(g_response, "(%d)", i);
	print(g_response, 15, 0);
}

void Prepend(char* s, const char* t)
{
	size_t len = strlen(t);
	size_t i;

	memmove(s + len, s, strlen(s) + 1);

	for (i = 0; i < len; ++i)
	{
		s[i] = t[i];
	}
}

int IndexOf(char* values, char find)
{
	int index;
	const char* ptr = strchr(values, find);
	if (ptr)
	{
		index = (int) (ptr - values);
	} else index = -1;
	return index;
}

char IntToChar(int c)
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

	for (; fstr[IndexOf(fstr, '.') + 1 + i] != '\0'; i++)
	{
		mstr[i] = fstr[IndexOf(fstr, '.') + 1 + i];
	}
	return atoi(mstr);
}

int StrCut(char* str, int begin, int len)
{
	int l = strlen(str);

	if (len < 0) len         = l - begin;
	if (begin + len > l) len = l - begin;
	memmove(str + begin, str + begin + len, l - len + 1);

	return len;
}

int IsEven(double d)
{
	double int_part;
	modf(d / 2.0, &int_part);
	return 2.0 * int_part == d;
}

double RoundIEEE754(double d)
{
	double i = floor(d);
	d -= i;
	if (d < 0.5)
		return i;
	if (d > 0.5)
		return i + 1.0;
	if (IsEven(i))
		return i;
	return i + 1.0;
}

float StringToFloat(char* in)
{
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

static double PRECISION              = 0.00000000000001;
static int    MAX_NUMBER_STRING_SIZE = 32;

/**
 * Double to ASCII
 * Same function as FloatToString, but may have a slightly different mantissa and precision
 */
char* FloatToString2(double n, char* s)
{
	int useExp;
	// handle special cases
	if (isnan(n))
	{
		strcpy(s, "nan");
	} else if (isinf(n))
	{
		strcpy(s, "inf");
	} else if (n == 0.0)
	{
		strcpy(s, "0");
	} else
	{
		int digit, m, m1;
		char* c = s;
		int neg = (n < 0);
		if (neg)
			n  = -n;
		// calculate magnitude
		m      = log10(n);
		useExp = (m >= 14 || (neg && m >= 9) || m <= -9);
		if (neg)
			*(c++) = '-';
		// set up for scientific notation
		if (useExp)
		{
			if (m < 0)
				m -= 1.0;
			n  = n / pow(10.0, m);
			m1 = m;
			m  = 0;
		}
		if (m < 1.0)
		{
			m = 0;
		}
		// convert the number
		while (n > PRECISION || m >= 0)
		{
			double weight = pow(10.0, m);
			if (weight > 0 && !isinf(weight))
			{
				digit = floor(n / weight);
				n -= (digit * weight);
				*(c++) = '0' + digit;
			}
			if (m == 0 && n > 0)
				*(c++)    = '.';
			m--;
		}
		if (useExp)
		{
			// convert the exponent
			int i, j;
			*(c++) = 'e';
			if (m1 > 0)
			{
				*(c++) = '+';
			} else
			{
				*(c++) = '-';
				m1 = -m1;
			}
			m      = 0;
			while (m1 > 0)
			{
				*(c++) = '0' + m1 % 10;
				m1 /= 10;
				m++;
			}
			c -= m;
			for (i = 0, j = m - 1; i < j; i++, j--)
			{
				// swap without temporary
				c[i] ^= c[j];
				c[j] ^= c[i];
				c[i] ^= c[j];
			}
			c += m;
		}
		*(c) = '\0';
	}
	return s;
}

void Zero(char* ptr, int c)
{
	int i = 0;
	for (; i < c; i++)
	{
		ptr[i] = (char) NULL;
	}

}

void FloatToStringPretty(float in, int digitLen, char* out)
{
	int decPlace, i;
	// Weird isolated case
	if (in == 10)
	{
		sprintf(out, "%d", 10);
		return;
	}
	FloatToString2(in, out);
	decPlace = IndexOf(out, '.');
	//sprintf(g_response, ". @ %d", decPlace);
	//print(g_response, 0, 2);
	//sprintf(g_response, "|%s|", out);
	//print(g_response, 0, 3);
	if (decPlace <= -1)
	{
		return;
	}
	i = (digitLen + decPlace + 1);

	for (; i > digitLen; i--)
	{
		out[i] = '\0';
	}
}