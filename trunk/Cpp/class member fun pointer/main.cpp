#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

typedef int (*FunPtrCall)(int a, int b);

int ExtCompute(int a, int b)
{
	return (a+b);
}


class myClass
{
public: 

	typedef int (myClass::*calc)(int a, int b);
	
	calc funptr;
	FunPtrCall funextptr;

	int compute(int a, int b)
	{
		return (a+b);
	}

	void set_cb_ptr(calc ptr)
	{
		funptr = ptr;
	}

	void call_cb_func()
	{
		int c = (this->*funptr)(100,300);
		cout << c << endl;
		getchar();
	}

private:

};


class my2ndClass
{
public: 

	typedef int (my2ndClass::*calc)(int a, int b);

	calc funptr;
	FunPtrCall funextptr;

	void set_ext_ptr(FunPtrCall ptr)
	{
		funextptr = ptr;
	}

	void set_cb_ptr(calc ptr)
	{
		funptr = ptr;
	}

	void call_cb_func()
	{
		int c = (this->*funptr)(100,300);
		cout << c << endl;
		getchar();
	}

	void call_ext_func()
	{
		int c = (*funextptr)(100,300);
		cout << c << endl;
		getchar();
	}

private:

};


int main()
{
	my2ndClass mc;

	//mc.set_cb_ptr(&ExtCompute);
	//mc.call_cb_func();

	mc.set_ext_ptr(&ExtCompute);
	mc.call_ext_func();

	return 0;
}