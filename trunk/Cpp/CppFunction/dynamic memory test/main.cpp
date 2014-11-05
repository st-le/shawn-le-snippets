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


/** @function main */
int main( int argc, char** argv )
{
	char s[100];
	int size[100] = {1};
	
	// Input sparser
	for(int i=1; i<argc; i++)
	{
		strcpy(s, argv[i]);
		printf("input[%d] = %s\n",i,s);
	
		sscanf(s, "%d", &size[i]);
		printf("size[%d] = %d\n\n",i,size[i]);
		//argv++;
	}

	// init dynamic memory
	int *int_ar = new int[size[1]];

	// why not use vector?? => ############ SOLUTION IS TO USE STL VECTOR!!!!! ############ 
	vector<vector<int>> int_2dar;

//	int **int_2dar = new int[size[1]][size[2]];
//	double*** dbl_ar = new double[size[1]][size[2]][size[3]];
	
	getchar();

	return 0;
}
