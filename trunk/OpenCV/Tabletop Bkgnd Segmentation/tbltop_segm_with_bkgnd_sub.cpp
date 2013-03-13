// v1.0 02/01/13: segment DOS application
// v2.0 23/02/13: still problems with the reading image/folder sparsing part
// v3.0 03/03/13: using new FolderSparser with Boost library
//				  -> some kind of stack over flow, memory allocation when read in more than 1500 images in a vector => silly programming error (bug)


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

#include "BumbleBee2.h"

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


int getCOM(const Mat frame3D, float& x, float& y, float& z)
{
	float x_acc = 0;
	float y_acc = 0;
	float z_acc = 0;
	float a,b,c;
	int cnt = 0;

	for (int i=0; i<frame3D.rows; i++)
		for (int j=0; j<frame3D.cols; j++)
		{
			a = frame3D.at<Vec3f>(i,j)[0];
			b = frame3D.at<Vec3f>(i,j)[1];
			c = frame3D.at<Vec3f>(i,j)[2];

			if((a!=0)||(b!=0)||(c!=0))
			{
				cnt++;
				x_acc = x_acc + a;
				y_acc = y_acc + b;
				z_acc = z_acc + c;
			}			
		}

	x = x_acc/cnt;
	y = y_acc/cnt;
	z = z_acc/cnt;

	return 1;
}

int main(int argc, char** argv)
{
	BumbleBee2 bb2;

	// stereo vars
	Mat frameRGB = Mat::zeros(5, 10, CV_8UC3);
	Mat frame3D;
	Mat rawframe, recframe, dispframe;
	// ***********

	// bkgnd sub vars
	char* bkgnd_img = "background.jpg";
	BackgroundSubtractorMOG bgsubtractor;
	Mat bgmask, bgimg, segimg;
	int bgflg = 0;       // to invoke segmentation
	Mat tmp;
	float x,y,z;
	// ***********


//	bb2.getframe(frame);

	while (1)
	{
		//bb2.getframe(rawframe, recframe, dispframe);

		bb2.getframe16(recframe, frameRGB, frame3D);
		
		imshow("stereo RGB image",frameRGB);
		/*imshow("stereo raw image",rawframe);
		imshow("stereo rectified image",recframe);
		imshow("stereo disparity image",dispframe);*/

		imshow("stereo 8bit rectified image",recframe);

		//cout << frame3D.at<Vec3f>(120, 160)[2] << endl;

		
		// ***segmentation
		if (bgflg)
		{
			recframe.copyTo(segimg);

			bgsubtractor(segimg, bgmask, 0);

			refineSegments(segimg, bgmask, tmp);

			cvtColor(segimg, segimg, CV_GRAY2BGR);

			/*cout << "segimg info = \n";
			MatInfo(segimg);
			cout << "tmp info = \n";
			MatInfo(tmp);*/

			multiply(segimg, tmp, segimg, 1);    // mask is applied to image here

			tmp.convertTo(tmp, CV_32FC3, 1, 0);
			multiply(frame3D, tmp, frame3D, 1);  // mask is applied to 3D points

			getCOM(frame3D, x, y, z);

			printf("COM: (%0.2f, %0.2f, %0.2f)\n",x,y,z);

			imshow("segment result", segimg);   // segimg -> CV_8UC3 image
			waitKey(1);

			//sprintf(tmp_c1,"%s/segment_%d.jpg",argv[1],i);
			//imwrite(tmp_c1, img_arr[i]);			
		}


		// ***read key & response
		char c = waitKey(1);

		if (c==27) break;
		else
			if (c=='t')
			{
				bgflg = 1;

				printf(" ############ Start training!! ############ \n");

				// ***output background image
				imwrite(bkgnd_img, recframe);
				
				// ***read background image & train
				bgimg = imread(bkgnd_img, 1);
				bgsubtractor.noiseSigma = 10;
				callTrainingBkGnd(bgimg, bgsubtractor, bgmask);
			}
	}

	return 1;
}