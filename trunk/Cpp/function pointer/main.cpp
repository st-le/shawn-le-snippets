#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

typedef void (* vFunctionCall)(int args);

typedef int (* calc)(int a, int b);


int compute(int a, int b)
{
	return (a+b);
}


void calculation(int a, int b, int& c, calc funptr)
{
	c = funptr(a,b);
}


void funct(int a, vFunctionCall funct2)
{
	funct2(a);
}

void otherFunct(int a)
{
	printf("%i", a);
}

int main()
{
	//funct(2, (vFunctionCall)otherFunct);

	int c;
	calculation(100,2,c, (calc)compute);
	cout << c << endl;
	getchar();
	return 0;
}