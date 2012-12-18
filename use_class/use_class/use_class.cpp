// use_class.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
using namespace std;

class CRectangle {
	int *width,*height;
public:
	CRectangle(int,int);
	~CRectangle();
	int area() {return (*width**height);}
};


CRectangle::CRectangle (int a, int b)   // constructor
{
	width = new int;
	height = new int;
	*width = a;
	*height = b;
}

CRectangle::CRectangle (int a, int b)   // overloading constructor
{
	width = new int;
	height = new int;
	*width = a;
	*height = b;
}

CRectangle::~CRectangle()	// destructor
{
	delete width;
	delete height;
}


int _tmain(int argc, _TCHAR* argv[])
{
	CRectangle rect(3,4);
	CRectangle rectb(5,6);
	
	cout << "area:" << rect.area() << endl;
	cout << "areab:" << rectb.area() << endl;
	getchar();
	return 0;
}

