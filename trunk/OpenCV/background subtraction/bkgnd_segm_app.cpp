// v1.0 02/01/13: segment DOS application
// v2.0 23/02/13: still problems with the reading image/folder sparsing part
// v3.0 03/03/13: using new FolderSparser with Boost library
//				  -> some kind of stack over flow, memory allocation when read in more than 1500 images in a vector
//                -> reduce number of image in folder -> works OK
//				  -> not really the number of image matters -> something else

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/video/background_segm.hpp"
#include <stdio.h>
#include <string>

#include <cstdio>
#include <iostream>
#include <fstream>

#include "OpenCV/MatWork.hpp"

#include "global.h"
#include "bkgnd_segm.h"
#include "FolderSparser.h"

using namespace cv;
using namespace std;

void help()
{
	printf("\n"
			"This program demonstrated a simple method of connected components clean up of background subtraction\n"
			"When the program starts, it begins learning the background.\n"
			"You can toggle background learning on and off by hitting the space bar.\n"
			"Call\n"
			"./segment_objects [video file, else it reads camera 0]\n\n");
}


int main(int argc, char** argv)
{

	if (argc != 4)
	{
		printf("Usage: app.exe img_directory file_list_name bkgnd_image");
		getchar();
		return 1;
	}
	/*else
	{
		printf(argv[1]);
		cout << argv[0] << endl; 
		getchar();
	}*/

	
  	// STEP 1: sparse the text file & read the images
	vector<Mat> img_arr;

	//FolderSparser(argv[1], argv[2], img_arr);
	//GetImageinDir(argv[1], img_arr);
	Mat img = imread(".\Test_database\GreenCart\0_0\GreenCart00_00_110.jpg",1);
	img_arr.push_back(img);
	cout << img_arr.size() << endl;

	//getchar();	
	char tmp_c[FULLNAME_SZ];
	sprintf(tmp_c,"%s/%s",argv[1],argv[3]);
	//cout << tmp_c << endl;
	// next time: put guards around these commands
	Mat bgimg = imread(tmp_c, 1);
	//imshow("background", bgimg);
	//waitKey(0);

	BackgroundSubtractorMOG bgsubtractor;
	Mat bgmask;

	bgsubtractor.noiseSigma = 10;
	callTrainingBkGnd(bgimg, bgsubtractor, bgmask);


	// Apply on images
	Mat tmp;
	char tmp_c1[FULLNAME_SZ];
	for (int i=0; i<img_arr.size(); i++)
	{
		bgsubtractor(img_arr[i], bgmask, 0);

		refineSegments(img_arr[i], bgmask, tmp);

		//tmp.copyTo(test_db_img[i]);

		multiply(img_arr[i], tmp, img_arr[i], 1);

		imshow("segment result", img_arr[i]);
		waitKey(1);

		sprintf(tmp_c1,"%s/segment_%d.jpg",argv[1],i);
		imwrite(tmp_c1, img_arr[i]);
	}

	getchar();

	return 1;
	
}
