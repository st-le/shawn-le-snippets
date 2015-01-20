// use for Mat matrix

#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/calib3d/calib3d.hpp"

//#include "CoordTransf.hpp"

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
using namespace cv;

/** Function Headers */

/** Global variables */


/** @function main */
int main( int argc, const char** argv )
{
	Mat matrix;
	FileStorage fs("file.yaml", FileStorage::READ);	
	if (!fs.isOpened())
	{
		printf("Error: camMatFile cannot read!\n");
	}
	fs["matrix"] >> matrix;

	cout << matrix << endl;
	getchar();

	return 0;
}
