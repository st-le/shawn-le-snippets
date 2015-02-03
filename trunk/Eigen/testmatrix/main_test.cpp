// use for Mat matrix

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>

#include <Eigen/Core> 
//#include <Eigen/Array> 
#include <Eigen/Geometry> 


using namespace std;
using namespace Eigen;
using Eigen::MatrixXd;

/** TypeNames */
//typedef Matrix<double, Dynamic, 1> VectorXd;

/** Function Headers */

/** Global variables */

 
/** @function main */
int main( int argc, const char** argv )
{
	MatrixXd m(4,4);
	m << 1, 2, 3, 4,
		 5, 6, 7, 8, 
		 9, 0, 1, 3,
		 4, 5, 6, 7;
	
	cout << "m" << endl << m << endl;

	cout << "norm col" << endl << m.colwise().hnormalized() << endl;   // normalized I want!
	cout << "norm row" << endl << m.rowwise().hnormalized() << endl;

	
	getchar();

	return 0;
}
