//
// Created by Decimation on 4/3/2018.
//

#ifndef TICALC_LIBRARY_H
#define TICALC_LIBRARY_H


#include <string.h>
#include <stdio.h>

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

int indexOf(char* values, char find) {
	int index;
	const char *ptr = strchr(values, find);

	index = ptr - values;
	return index;
}

char intToChar(int c)
{
	return c + '0';
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

void FloatToString(float f, char* out)
{
	char temp[10];
	int ipart = (int) f;
	// Will create something like %.mantissa on the calculator
	sprintf(out, "%g", f);


	sprintf(temp, "%d", ipart);

	// We can do this
	//temp[indexOf(temp, intToChar(ipart))] = '\0';

	// or this
	str_cut(out, 0, 1);

	prepend(out, temp);
}

#endif //TICALC_LIBRARY_H
