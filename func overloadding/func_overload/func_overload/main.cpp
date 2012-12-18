#include <iostream>

using namespace std;


int add(int a, int b)
{
	return a+b;
}

float add(float a, float b)
{
	return a+b;
}

int main()
{
	float af =3.5;
	float bf = 0.1;

	int ai = 1;
	int bi = 2;

	cout << "float = " << add(af,bf) <<endl;
	cout << "integ = " << add(ai,bi) <<endl;
	getchar();

	return 0;
}