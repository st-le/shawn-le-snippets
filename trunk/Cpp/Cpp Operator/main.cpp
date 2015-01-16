#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


/** @function main */
int main( int argc, char** argv )
{

	void *vptr;

	// void pointer cannot be used like this
	vptr = "abcd";
	int i = 103;
	vptr = &i;
	cout << vptr << endl;
	getchar();

	// void pointer cannot be used like this
	// 1st cast (int *) casts void* to int*
	// 2nd * is value of pointee that the int* pointer is pointing too
	cout << *(int *)vptr << endl;

	getchar();

	return 0;
}
