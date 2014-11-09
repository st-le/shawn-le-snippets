#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
//using namespace cv;

/** Function Headers */

/** Global variables */

string window_name = "Color Segmentation";
  
float data[] = {1,2,3,4,5};

//float data[2][5] = {{1,2,3,4,5},{7,8,9,10,11}};


class myClassSmall
{
private:

	string a,b;

public: 

	myClassSmall(string a_in, string b_in)
	{
		a = a_in;
		b = b_in;
	}

	~myClassSmall()
	{

	}

};

class myClassBig
{
private:

	myClassSmall sc;

public: 

	myClassBig(string a_inp, string b_inp) :
											sc(a_inp, b_inp)
	{

	}

	~myClassBig()
	{

	}

};


/** @function main */
int main( int argc, char** argv )
{

	string str_a = "letrung";
	string str_b = "babhe";
	myClassBig mCB(str_a, str_b);


		
	getchar();

	return 0;
}
