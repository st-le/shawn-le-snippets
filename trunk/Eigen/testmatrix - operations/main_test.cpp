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
	MatrixXd m(2,2);
	m(0,0) = 3;
	m(1,0) = 2.5;
	m(0,1) = -1;
	m(1,1) = m(1,0) + m(0,1);
	std::cout << m << std::endl;

	Vector4d a(1,2,3,4);
	Vector4d b = a;
	Vector4d c = b+a;
	Matrix3f d;
	d << 1, 2, 3,
	     4, 5, 6, 
		 7, 8, 9;

	cout << a << endl << endl;
	cout << b << endl << endl;
	cout << c << endl << endl;
	cout << 2.0*d << endl << endl;
	getchar();

	Matrix3f A;
	Vector3f e;
	A << 1,2,3,  4,5,6,  7,8,10;
	e << 3, 3, 4;
	Vector3f x = A.inverse() * e;
	cout << "The solution is:" << endl << x << endl;
	getchar();


	Vector3f f;
	A << 1,2,3,  4,5,6,  7,8,9;
	f << 3, 3, 4;
	cout << "Here is the matrix A:" << endl << A << endl;
	cout << "Here is the vector b:" << endl << b << endl;
	Vector3f y;
	y = A.lu().solve(f);
	cout << "The solution is:" << endl << y << endl;
	getchar();

	return 0;
}
