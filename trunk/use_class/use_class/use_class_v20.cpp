// use_class.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
using namespace std;

class CRectangle {
	int *width,*height;
public:
	CRectangle(int,int);
	CRectangle();
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

CRectangle::CRectangle ()   // overloading constructor
{
	width = new int;
	height = new int;
	*width = 5;
	*height = 5;
}

CRectangle::~CRectangle()	// destructor
{
	delete width;
	delete height;
}


int _tmain(int argc, _TCHAR* argv[])
{
	CRectangle rect(3,4);
	CRectangle rectb;
	
	cout << "area:" << rect.area() << endl;
	cout << "areab:" << rectb.area() << endl;
	getchar();
	return 0;
}

