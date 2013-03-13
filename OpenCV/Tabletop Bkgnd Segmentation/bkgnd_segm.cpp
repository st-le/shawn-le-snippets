#include "bkgnd_segm.h"
#include "global.h"

using namespace std;
using namespace cv;

//const uchar NTIMES = 15;

void refineSegments(const Mat& img, Mat& mask, Mat& dst)
{
	int niters = 3;

	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	Mat temp;

	dilate(mask, temp, Mat(), Point(-1,-1), niters);
	erode(temp, temp, Mat(), Point(-1,-1), niters*2);
	dilate(temp, temp, Mat(), Point(-1,-1), niters);

	findContours( temp, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );

	dst = Mat::zeros(img.size(), CV_8UC3);  // for database built app
	//dst = Mat::zeros(img.size(), CV_8UC1);    // for tabletop project

	if( contours.size() == 0 )
		return;

	// iterate through all the top-level contours,
	// draw each connected component with its own random color
	int idx = 0, largestComp = 0;
	double maxArea = 0;

	for( ; idx >= 0; idx = hierarchy[idx][0] )
	{
		const vector<Point>& c = contours[idx];
		double area = fabs(contourArea(Mat(c)));
		if( area > maxArea )
		{
			maxArea = area;
			largestComp = idx;
		}
	}
	//Scalar color( 0, 0, 255);
	Scalar color( 1, 1, 1);
	drawContours( dst, contours, largestComp, color, CV_FILLED, 8, hierarchy );
}


int callTrainingBkGnd(const Mat background, 
						BackgroundSubtractorMOG& bgsubtractor, Mat& bgmask)
{

	Mat tmp_frame, out_frame;

	/*if (background == NULL)
	{*/
	//	cout << "background=" << endl;
	//	MatInfo(background);
	//	printf("There is no input background!!");
	//	getchar();
	//	return 0;
	//}

	background.copyTo(tmp_frame);
    
    namedWindow("video", 1);
    namedWindow("segmented", 1);
    
	Mat tmp_mat;
    
	int cnt_img = 0;
	int keycode;

	// TRAINING BACKGROUND: input background (image)
	for (int i=0; i<NTIMES; i++)
	{
		
		//bgsubtractor(tmp_frame, bgmask, update_bg_model ? -1 : 0);    // bgmask is the coarse learnt background
		bgsubtractor(tmp_frame, bgmask, -1);    // bgmask is the coarse learnt background
		//CvMat _bgmask = bgmask;
		//cvSegmentFGMask(&_bgmask);

		/*cout << "tmp_frame=" << endl;
		MatInfo(tmp_frame);
		cout << "bgmask=" << endl;
		MatInfo(bgmask);
		cout << "out_frame=" << endl;
		MatInfo(out_frame);
		getchar();*/

		refineSegments(tmp_frame, bgmask, out_frame);  // out_frame is the refined mask
		imshow("video", tmp_frame);
		imshow("segmented", out_frame);
		//imshow("bkgnd mask", bgmask);

		// use the refined mask to segment wc stream
		/*MatInfo(out_frame);
		getchar();
		MatInfo(tmp_frame);
		getchar();*/
		multiply(tmp_frame, out_frame, tmp_mat, 1);
		imshow("Segmented stream",tmp_mat);
 
		waitKey(1);
	}

	printf("Done for training background\n");
//	getchar();

	return 1;
}