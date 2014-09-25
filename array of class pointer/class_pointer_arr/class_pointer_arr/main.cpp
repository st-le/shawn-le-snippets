
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "mathwork.hpp"

using namespace std;


void main()
{

	// Init array of pointers
	mathwork* mw_ptr[10];

	mw_ptr[0] = new mathwork(3,2);
	mw_ptr[1] = new mathwork;

	printf("plus of mw_ptr[0] = %0.2f\n", mw_ptr[0]->plus());

	cout << "num of instances:" << mathwork::count << endl << endl;
	getchar();

	printf("mw_ptr[0].minus = %0.2f\n",mw_ptr[0]->minus());
	getchar();

	// Init class objects beforehand
	printf(" ######### SECOND TEST #########\n");
	mathwork mw0 = mathwork(15, 5);
	mathwork mw1 = mathwork(9, -3);

	mathwork* mw_ptr_2nd[10];
	mw_ptr_2nd[0] = &mw0;
	mw_ptr_2nd[1] = &mw1;

	printf("plus of mw_ptr_2nd[0] = %0.2f\n", mw_ptr_2nd[0]->plus());
	printf("minus of mw_ptr_2nd[0] = %0.2f\n", mw_ptr_2nd[0]->minus());
	getchar();
}