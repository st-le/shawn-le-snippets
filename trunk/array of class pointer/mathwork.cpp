#include "mathwork.hpp"


int mathwork::count=0;

	
mathwork::mathwork()
	{
		a = 0;
		b = 0;

		count++;
	};

mathwork::mathwork(double a_inp, double b_inp)
	{
		a = a_inp;
		b = b_inp;

		count++;
	}

mathwork::~mathwork()
{

}

double mathwork::plus()
	{
		return a+b;
	}

double mathwork::minus()
	{
		return a-b;
	}
