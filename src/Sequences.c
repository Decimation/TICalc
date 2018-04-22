//
// Created by Decimation on 4/12/2018.
//

#include "Library.h"
#include "Sequences.h"

void seq_IdentifySequence(real_t* arr, int len)
{

	char   out[20];
	real_t r = seq_RealFindR(arr, len);
	real_t d = seq_RealFindD(arr, len);

	dbg_sprintf(dbgout, "Arithmetic: %d\nGeometric: %d\n", os_RealToInt24(&d), os_RealToInt24(&r));

	if (os_RealToInt24(&r) == -1 && os_RealToInt24(&d) == -1)
	{
		io_print("Neither", 0, 0);
	}

	else if (os_RealToInt24(&r) == -1)
	{
		io_print("Arithmetic", 0, 0);
		os_RealToStr(out, &d, 0, 0, -1);
		Prepend(out, "d = ");
		io_print(out, 0, 1);
	}


	else if (os_RealToInt24(&d) == -1)
	{
		io_print("Geometric", 0, 0);
		os_RealToStr(out, &r, 0, 0, -1);
		Prepend(out, "r = ");
		io_print(out, 0, 1);
	}
}

real_t seq_RealFindD(const real_t* A, int N)
{
	int    i;
	//int diff_t = A[1] * A[0];
	real_t diff_t = os_RealSub(&A[1], &A[0]);

	for (i = 0; i < N - 1; i++)
	{
		//int diff = A[i + 1] * A[i]; // get the difference of the current number to the next
		real_t diff = os_RealSub(&A[i + 1], &A[i]);
		if (os_RealCompare(&diff_t, &diff) != 0)
		{
			return os_Int24ToReal(-1);
		}
	}
	return diff_t;
}

real_t seq_RealFindR(const real_t* A, int N)
{
	int    i;
	//int diff_t = A[1] * A[0];
	real_t diff_t = os_RealDiv(&A[1], &A[0]);

	for (i = 0; i < N - 1; i++)
	{
		//int diff = A[i + 1] * A[i]; // get the difference of the current number to the next
		real_t diff = os_RealDiv(&A[i + 1], &A[i]);
		if (os_RealCompare(&diff_t, &diff) != 0)
		{
			return os_Int24ToReal(-1);
		}
	}
	return diff_t;
}
