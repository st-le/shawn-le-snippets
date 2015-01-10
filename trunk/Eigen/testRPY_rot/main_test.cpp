// use for Mat matrix

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>

#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/calib3d/calib3d.hpp"

#include <Eigen/Core> 
//#include <Eigen/Array> 
#include <Eigen/Geometry> 

#include "opencv2/core/eigen.hpp"

using namespace std;
using namespace Eigen;
using namespace cv;

/** Function Headers */

/** Global variables */

string window_name = "Color Segmentation";
  
//float data[] = {1,2,3,4,5};

float data[10] = {1,2,3,4,5,7,8,9,10,11};
//double data[10] = {1,2,3,4,5,7,8,9,10,11};    // cannot use double




/** @function main */
int main( int argc, const char** argv )
{

	Matrix3f m;

	m = AngleAxisf(0.25*M_PI, Vector3f::UnitX())
      * AngleAxisf(0.5*M_PI, Vector3f::UnitY())
      * AngleAxisf(0.33*M_PI, Vector3f::UnitZ());

	cout << "original rotation:" << endl;
	cout << m << endl << endl;

	Vector3f ea = m.eulerAngles(0, 1, 2); 
	cout << "to Euler angles:" << endl;
	cout << ea << endl << endl;

	Matrix3f n;
	n = AngleAxisf(ea[0], Vector3f::UnitX())
	   *AngleAxisf(ea[1], Vector3f::UnitY())
	   *AngleAxisf(ea[2], Vector3f::UnitZ()); 
	cout << "recalc original rotation:" << endl;
	cout << n << endl;

	// void eigen2cv(const Eigen::Matrix<_Tp, _rows, _cols, _options, _maxRows, _maxCols>& src, Mat& dst)
	Mat eaMat;
	eigen2cv(ea, eaMat);
	cout << "OpenCV result" << endl;
	cout << eaMat << endl;
	
	getchar();

	return 0;
}
