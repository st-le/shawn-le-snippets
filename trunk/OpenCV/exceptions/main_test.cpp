// use for Mat matrix

#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/calib3d/calib3d.hpp"

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
using namespace cv;

/** Function Headers */

/** Global variables */


int process(Mat mtx)
{
	int ret = 0;

	try
	{
		mtx.at<double>(3,4) = 1.3;
	}
	catch( cv::Exception& e )
	{
		const char* err_msg = e.what();
		std::cout << "exception caught: " << err_msg << std::endl;
	}

	return ret;
}


/** @function main */
int main( int argc, const char** argv )
{


	Mat mtx = imread("image.jpg", 1);

	process(mtx);

	return 0;
}
