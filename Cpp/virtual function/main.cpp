#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


class Polygon
{
public:

	Polygon(vector<int> sides_in)
	{};
	
	int GetArea(){};

	int GetAB(int a, int b)	{ };

private:

	vector<int> sides;
};


class Triangle: public Polygon
{
public:

	Triangle(vector<int> sides_in);
	
	int GetArea()
	{
		return (sides[0]*sides[1]);
	};

	int GetAB(int a, int b, int c)	
	{
		a = 1;
		b = 2; 
		c = 3;
		return 1;
	};

private:

	vector<int> sides;
};



class Rectangle: public Polygon
{
public:

	Rectangle(vector<int> sides_in);
	
	int GetArea()
	{
		return (sides[0]*sides[1]);
	};

private:

	vector<int> sides;
};




/** @function main */
int main( int argc, char** argv )
{
	vector<int> sides;
	sides.push_back(5);
	sides.push_back(3);
	sides.push_back(5);
	Polygon plg(sides);

	sides.clear();
	sides.push_back(5);
	sides.push_back(3);
	sides.push_back(5);
	Triangle triag(sides);

	int a,b,c;
	triag.GetAB(a,b,c);

	return 0;
}
