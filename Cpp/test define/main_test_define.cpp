
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <iostream>

using namespace std;

#define SQUARE(x)  ((x) * (x))

int f()
{
	return 10;
}

int main( int argc, char** argv )
{
	int b = 3;
	cout << SQUARE(b) << endl;
	cout << "SQUARE(f) ";
	cout << SQUARE(f()) << endl;
	getchar();

    return 0;
}
