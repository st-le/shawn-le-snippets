// test_diff_src_files.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "minus_module.h"
#include "dijsktra.h"
#include "test.h"

//int glb_val = 0;  <- global variable cannot be shared like this
int arr[4];
int arr2d[2][2] = {
					{-1,  5}, 
					{ 5, -1}
				 };

int arr3[] = {100,100,100,100};
int arr4[4][4];

int L[MAX_VTX][MAX_VTX] ={
	{-1,  5, -1, -1, -1,  3, -1, -1}, 
	{ 5, -1,  2, -1, -1, -1,  3, -1}, 
	{-1,  2, -1,  6, -1, -1, -1, 10}, 
	{-1, -1,  6, -1,  3, -1, -1, -1},
	{-1, -1, -1,  3, -1,  8, -1,  5}, 
	{ 3, -1, -1, -1,  8, -1,  7, -1}, 
	{-1,  3, -1, -1, -1,  7, -1,  2}, 
	{-1, -1, 10, -1,  5, -1,  2, -1} 
};



int plus_module(int a,int b)
{
	return a+b;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int a = 3;
	int b = 5;

	arr[0] = 0;
	arr[1] = 1;
	arr[2] = 2;
	arr[3] = 3;

	printf("a+b = %d\n",plus_module(a,b));
	printf("a-b = %d\n",minus_module(a,b));
	printf("global val = %d\n",glb_val);
	update_arr(arr3);
	update_arr(arr);
	update_arr2d(arr2d);

	for(int i=0;i<4;i++)
	{
		printf("arr[%d]= %d\n",i,arr3[i]);
	}

	printf("array 2d = \n");

	for(int i=0;i<2;i++)
	{
		for(int j=0;j<2;j++)
			printf("arr2d[%d,%d]= %d\n",i,j,arr2d[i][j]);

		printf("\n");
	}

	
	// test Dijsktra
	callDijsktra(L,8);
	

	getchar();

	return 0;
}

