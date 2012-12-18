// CppFunction.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>

using namespace std;

void prevnext(int x, int& prev, int& next)
{
	prev = x-1;
	next = x+1;
}

void duplicate (int& a, int& b, int& c)
{
	a*= 2;
	b*= 2;
	c*= 2;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int x= 100, y,z;
	string str("");

	prevnext(x, y, z);
	
	cout<< "Previous =" << y << ", Next =" << z << endl;

	duplicate(x, y, z);

	cout << "x =" << x << ", y=" << y << ", z=" << z << endl;

	getchar();

	return 0;
}

