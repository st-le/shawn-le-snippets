// use_class.cpp : Defines the entry point for the console application.
// this one doesn't use pointer vars in class => no need a destructor

#include "stdafx.h"
#include "iostream"
using namespace std;

class CRectangle {
	int width,height;
public:
	CRectangle(int,int);
	int area() {return (width*height);}
};


CRectangle::CRectangle (int a, int b)   // constructor
{
	width = a;
	height = b;
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

