// v1.0 24/09/12 my version, using v2.4 feature classes in nonfree, finish constructor & extracting features
// v1.2 24/09/12 matching features
// v1.3 25/09/12 matching features using Descriptor Matcher of OpenCV i.e. BFmatcher
// v1.5 25/09/12 modify to use only defined points i.e. 100 strongest points

/*
 * A Demo to OpenCV Implementation of SURF
 * Further Information Refer to "SURF: Speed-Up Robust Feature"
 * Author: Liu Liu
 * liuliu.1987+opencv@gmail.com
 */
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/features2d.hpp"     // SURF & SIFT headers have been moved here!!!!
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc_c.h"

#include <iostream>
#include <vector>
#include <stdio.h>

#include "MatWork.hpp"

using namespace std;
using namespace cv;

void help()
{
    printf(
        "This program demonstrated the use of the SURF Detector and Descriptor using\n"
        "either FLANN (fast approx nearst neighbor classification) or brute force matching\n"
        "on planar objects.\n"
        "Usage:\n"
        "./find_obj <object_filename> <scene_filename>, default is box.png  and box_in_scene.png\n\n");
    return;
}


int main(int argc, char** argv)
{

	Mat img = imread("box.png", 0);
	Mat img1 = imread("box_in_scene.png", 0);
	char *org_wind = "the box";
	char *scene_wind = "box in scene";


	SIFT SIFTdect_obj = SIFT(100, 3, 0.04, 10, 1.6);
	SIFT SIFTdect_img = SIFT(100, 3, 0.04, 10, 1.6);

	vector<KeyPoint> keypoints_obj, keypoints_img;
	Mat descriptors_obj, descriptors_img; 

	
	SIFTdect_obj(img, noArray(), keypoints_obj, descriptors_obj, false);  // noArray(): using no mask
	SIFTdect_img(img1, noArray(), keypoints_img, descriptors_img, false);

	cout << "object =" << endl;
	MatInfo(img);
	cout << "scene =" << endl;
	MatInfo(img1);
	MatInfo(descriptors_obj);
	//getchar();
	//MATmtxdisp(descriptors_obj);
	//getchar();
	
	MatInfo(descriptors_img);
	//getchar();
	//MATmtxdisp(descriptors_img);
	//getchar();
	

	Mat pnts_obj = Mat::zeros(1, keypoints_obj.size(), CV_32FC2);
	Mat pnts_img = Mat::zeros(1, keypoints_img.size(), CV_32FC2);
	
	for (int i = 0; i < keypoints_obj.size() ; i++)
	{
		//printf("(%0.2f, %0.2f)\n", keypoints_obj[i].pt.x, keypoints_obj[i].pt.y);
		pnts_obj.at<Vec2f>(i)[0] = keypoints_obj[i].pt.x;
		pnts_obj.at<Vec2f>(i)[1] = keypoints_obj[i].pt.y;
	}
	
	for (int i = 0; i < keypoints_img.size() ; i++)
	{
		//printf("(%0.2f, %0.2f)\n", keypoints_img[i].pt.x, keypoints_img[i].pt.y);
		pnts_img.at<Vec2f>(i)[0] = keypoints_img[i].pt.x;
		pnts_img.at<Vec2f>(i)[1] = keypoints_img[i].pt.y;
	}


	drawCircles(img, pnts_obj);
	drawCircles(img1, pnts_img);


	// Match keypoints with Brute Force Matcher
	BFMatcher kpMatcher(NORM_L2, false);

	vector<DMatch> matches;

	Mat mask = Mat::zeros(descriptors_obj.rows, descriptors_img.rows, CV_8UC1);
	//mask.at<float>(keypoints_obj[0].pt.y, keypoints_obj[0].pt.x) = descriptors_obj.at<float>(keypoints_obj[0].pt.y, keypoints_obj[0].pt.x);
	Mat maskinit = Mat::ones(100, descriptors_img.rows, CV_8UC1);
	maskinit.copyTo(mask(Range(0, 100), Range(0, descriptors_img.rows)));

	kpMatcher.match(descriptors_obj, descriptors_img, matches, mask);   // no use mask -> skip the arg

	// Show results of matching
	Mat outimg;
	

	drawMatches(img, keypoints_obj, img1, keypoints_img, matches, outimg);
		
	cout << "Number of matches = " << matches.size() << endl;

	//imshow(org_wind, img);
	//imshow(scene_wind, img1);
	imshow("Match result", outimg);

	waitKey(0);


    return 0;
}