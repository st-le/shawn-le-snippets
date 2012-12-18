#include <stdafx.h>

//#include "test.h"

void update_arr(int arr[])
{
	arr[0] = 50;
	arr[1] = 50;
	arr[2] = 50;
	arr[3] = 50;
}

void update_arr2d(int (&arr2d)[2][2])
{
	arr2d[0][0] = -100;
	arr2d[0][1] = -100;
	arr2d[1][0] = -100;
	arr2d[1][1] = -100;
}

int minus_module(int a,int b)
{
	glb_val = 1;

	return a+b;
}