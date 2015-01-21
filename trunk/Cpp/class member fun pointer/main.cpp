#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class myClass
{
public: 

	typedef int (myClass::*calc)(int a, int b);
	
	calc funptr;

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


int main()
{
	myClass mc;

	mc.set_cb_ptr(&myClass::compute);
	mc.call_cb_func();

	return 0;
}