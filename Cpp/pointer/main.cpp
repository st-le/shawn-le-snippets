#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


class Person
{
	
	
	public:

	Person()
	{
	};
	
	Person(double height_in, double income_in)
	{
		height = height_in;
		income = income_in;
	}
	
	
	~Person()
	{
	
	}
	
	double getHeight()
	{
		return height;
	}

	double getIncome()
	{
		return income;
	}
	
	Person operator+(const Person& B)
	{
		Person ret;
		
		// why use this but not height??
		//ret.height = (this->height + B.height)/2;
		//ret.income = this->income + B.income;
		ret.height = (height + B.height)/2;
		ret.income = income + B.income;


		return ret;
	}
	
	
	private:
	
	double height, income;

}; 


/** @function main */
int main( int argc, char** argv )
{
	Person A(172, 20000);
	Person B(145, 5000);
	
	// the grown up kid with inheritance
	Person C = A + B;
	
	printf("Result is\n");
	printf("%.2f\n",C.getHeight());
	printf("%.2f",C.getIncome());
	getchar();
	
	return 0;
}
