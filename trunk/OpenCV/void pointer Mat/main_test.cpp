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


/** @function main */
int main( int argc, const char** argv )
{


	VideoCapture cap;	
	cap = VideoCapture(0);

	if( !cap.isOpened() )
	{
		cout << "Could not initialize capturing...\n";
		getchar();

		return 0;
	}

	void* vptr;
	// ######### Mat and void pointer to Mat
	Mat frame;
	cap >> frame;
	
	//vptr = (void *)frame;  // not accepted
	//imshow("void pointer", *(Mat*)vptr);

	// This will be accepted
	Mat* mptr;
	mptr = &frame;

	vptr = (void*)mptr; 

	imshow("void pointer", *(Mat*)vptr);
	waitKey(0);
	// ######### vector and void pointer to vector
	vector<int> ivect;
	ivect.push_back(1);

	vector<int> *vtptr;
	vtptr = &ivect;

	vptr = (void*)vtptr;

	cout << (*(vector<int>*)vptr)[0] << endl;

	getchar();
	
	return 0;
}
