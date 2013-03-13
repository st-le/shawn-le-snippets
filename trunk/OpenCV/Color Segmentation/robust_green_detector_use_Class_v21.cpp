/*
v10: fix run-time error problem
v12: add a trackbar for color threshold
v14: (21/04/12) add a trackbar for detect threshold
v15: (28/04/12) record tuned para (thresholds, color sample)
v17: (06/05/12) add multiple wc views & multiple corresponding track bars (still working)
v2.0: (08/09/12) new direction starts: finish the application without Qt
*/

//#include "stdafx.h"

#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc_c.h"

#include <stdio.h>

#include <iostream>
#include <fstream>
#include <string>

#include "ColorDetector.h"

using namespace std;
using namespace cv;

// webcam frame
Mat frame;
Mat frame_segm; // segmented frame

// the class
ColorDetector ClrDet(Point3i(10,20,30), 50);

// Tuning parameters
double thres;

int detect_thres = 10000;
int color_thres = 30;
CvPoint clickPnt = cvPoint(50, 50);
char *model_file = "model.jpg";

// Record file
char* para_file = "parameters.rec";


const int MAX_CORNERS = 1000;
//IplImage* frame =0;	
cv::Point3i sample;
char wndname[] = "Camera";
char tbar_color[] = "Color Threshold";
char tbar_detect[] = "Detect Threshold";


int readTextFile(vector<string>& lines)
{
	string line;
	ifstream myfile (para_file);   
	if (myfile.is_open())
	{
		while ( myfile.good() )
		{
			getline (myfile,line);
			lines.push_back(line);   // append to vector
			//      cout << line << endl;
		}
		myfile.close();
	}

	else cout << "Unable to open file"; 

	//	getchar();
	return 0;
}

int writeTextFile()
{
	ofstream myfile;
	myfile.open (para_file);
	//	myfile << "I'm Le Trung Son\n";
	//	myfile << "This is the writing to file test\n";
	//	myfile << "Writing this to a file.\n";
	myfile << detect_thres << "\n";
	myfile << color_thres << "\n";
	myfile << sample.x << "\n";
	myfile << sample.y << "\n";
	myfile << sample.z;
	myfile.close();
	return 0;
}

// some frequent problem with mouse_clicking
void on_mouse( int event, int x, int y, int flags, void* param )  // this is same for both 2.3 & 2.1 versions
{
	//if(frame.empty()) exit;

	uchar ch1, ch2, ch3;	

	switch( event )
	{
	case CV_EVENT_LBUTTONDOWN:

		/*ch1 = ((uchar*)(frame->imageData + frame->widthStep*y))[x*3 + 0];
		ch2 = ((uchar*)(frame->imageData + frame->widthStep*y))[x*3 + 1];
		ch3 = ((uchar*)(frame->imageData + frame->widthStep*y))[x*3 + 2];*/

		ch1 = frame.at<Vec3b>(y,x)[0];
		ch2 = frame.at<Vec3b>(y,x)[1];
		ch3 = frame.at<Vec3b>(y,x)[2];

		sample.x = ch1;
		sample.y = ch2;
		sample.z = ch3;

		// update the class
		ClrDet.SampleUpdate(sample);

		printf("click point is (%d,%d) -> (R,G,B) = (%d,%d,%d)\n",y,x, sample.x, sample.y, sample.z);

		writeTextFile();

		break;
	case CV_EVENT_LBUTTONUP:
		break;
	}
}



void on_trackbar( int dummy )
{	
	printf("track_bar = %d/n",dummy);
	thres = dummy;

	ClrDet.ThresholdUpdate(thres);

	writeTextFile();
}


int main(int argc, char** argv) {
 
	Point3i sample;
	sample.x = 10;
	sample.y = 20;
	sample.z = 30;
	
	thres = 50;

	//ClrDet = ColorDetector(sample, threshold);

	// mouse click
	namedWindow("your frame", 1);
	setMouseCallback( "your frame", on_mouse, 0 );    // Mouse event init

	// track bar
	cvCreateTrackbar("Threshold", "your frame", &color_thres, 100, on_trackbar);  // track bar init
	
	// readWC
	VideoCapture cap(0); // open the default camera
	if(!cap.isOpened())  // check if we succeeded
		return -1;

	char c;
	while (1)
	{
		cap >> frame;

		// segment the frame
		ClrDet.Segment(frame, frame_segm);
		
		imshow("your frame", frame);
		imshow("segmented frame", frame_segm);

		c = waitKey(1);
		if (c==27) break;
	}

	return 0;
}