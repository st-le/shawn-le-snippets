
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <iostream>

using namespace std;

void func( int x )
{
    char* pleak = new char[1024]; // might be lost => memory leak
    std::string s( "hello world" ); // will be properly destructed

    if ( x ) throw std::runtime_error( "boom" );

    delete [] pleak; // will only get here if x == 0. if x!=0, throw exception
}

int func1( int x )
{
    string* pleak = new string[1024]; // might be lost => memory leak
    std::string s( "hello world" ); // will be properly destructed

    return 1;

    delete [] pleak; // will only get here if x == 0. if x!=0, throw exception
}


int main()
{
	for (int i=0; i<1000; i++)
	{

		char* str = new char[1024];

		try
		{
			func( 10 );
		}
		catch ( const std::exception& e )
		{
			cout << "error is thrown!\n";
			//return 1;
			//getchar();
		}

		func1(10);

		char c;
		//cin >> c;
		//if (c == 'c') break;
	}

	return 0;
}