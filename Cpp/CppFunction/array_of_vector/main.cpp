#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


int afun(vector<int> *points, int size)
{
	int ret = 1;

	for (int i=0; i<size; i++)
	{
	  for (int j=0; j<points[i].size(); j++)
	  {
	  	printf("%d ",points[i][j]);
	  }
		printf("\n");
	}


	return ret;
}


/** @function main */
int main( int argc, char** argv )
{
	vector<int> points[3];

	vector<int> pnts;
	pnts.push_back(1);
	pnts.push_back(2);
	pnts.push_back(3);
	pnts.push_back(4);

	points[0] = pnts;
	points[1] = pnts;
	points[2] = pnts;

	afun(points, 3);
	

	return 0;
}
