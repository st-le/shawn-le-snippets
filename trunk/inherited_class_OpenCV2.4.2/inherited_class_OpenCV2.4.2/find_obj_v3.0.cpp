// v1.0 24/09/12 my version, using v2.4 feature classes in nonfree, finish constructor & extracting features
// v1.2 24/09/12 matching features
// v1.3 25/09/12 matching features using Descriptor Matcher of OpenCV i.e. BFmatcher
// v1.5 25/09/12 modify to use only defined points i.e. 100 strongest points
// v2.0 26/09/12 use with fundamental matrix
// v3.0 26/09/12 find transformation between the two images using homography matrix 
//               change 100 to sample_sz

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

const int sample_sz = 20;

void help()
{
    printf(
        "This program demonstrated the use of the SURF Detector and Descriptor using\n"
        "either FLANN (fast approx nearest neighbor classification) or brute force matching\n"
        "on planar objects.\n"
        "Usage:\n"
        "./find_obj <object_filename> <scene_filename>, default is box.png  and box_in_scene.png\n\n");
    return;
}


int main(int argc, char** argv)
{
	//char *imgfile0 = "box.png";
	//char *imgfile0 = "Picture 98.jpg";
	char *imgfile0 = "Picture 100.jpg";
//	char *imgfile1 = "box_in_scene.png";
	//char *imgfile1 = "Picture 99.jpg";
	char *imgfile1 = "Picture 101.jpg";

	Mat img = imread(imgfile0, 0);
	Mat img1 = imread(imgfile1, 0);
	char *org_wind = "the box";
	char *scene_wind = "box in scene";


	SIFT SIFTdect_obj = SIFT(sample_sz, 3, 0.04, 10, 1.6);
	SIFT SIFTdect_img = SIFT(sample_sz, 3, 0.04, 10, 1.6);

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
	Mat maskinit = Mat::ones(sample_sz, descriptors_img.rows, CV_8UC1);
	maskinit.copyTo(mask(Range(0, sample_sz), Range(0, descriptors_img.rows)));

	kpMatcher.match(descriptors_obj, descriptors_img, matches, mask);   // no use mask -> skip the arg

	// Show results of matching
	Mat outimg;
	

	drawMatches(img, keypoints_obj, img1, keypoints_img, matches, outimg);
		
	cout << "Number of matches = " << matches.size() << endl;

	//imshow(org_wind, img);
	//imshow(scene_wind, img1);
	imshow("Match result", outimg);

	
	// Using FUNDAMENTAL matrix
	// read matches
	/*
	DMatch match = matches[0];
	cout << match.queryIdx << " matches with " << match.imgIdx << " img idx " << match.imgIdx << endl;
	
	for (int i = 0; i < matches.size(); i++)
	{
		match = matches[i];
		cout << match.queryIdx <<  " -> " << match.trainIdx << endl;
	}
	*/
	
	// extract matching points
	Mat matched_pnts_obj = Mat::zeros(1, matches.size(), CV_32FC2);
	Mat matched_pnts_img = Mat::zeros(1, matches.size(), CV_32FC2);

	DMatch match;
	//for (int i = 0; i < matches.size(); i++)
	//for (int i = 0; i < 4; i++)
	for (int i = 0; i < matches.size(); i++)
	{
		match = matches[i];
		//cout << match.queryIdx <<  " -> " << match.trainIdx << endl;
		matched_pnts_obj.at<Vec2f>(i) = keypoints_obj[0].pt;                // works OK!!!!
		matched_pnts_img.at<Vec2f>(i) = keypoints_img[match.queryIdx].pt;

		printf("(%0.2f, %0.2f) -> (%0.2f, %0.2f)\n",matched_pnts_obj.at<Vec2f>(i)[0],matched_pnts_obj.at<Vec2f>(i)[1], matched_pnts_img.at<Vec2f>(i)[0], matched_pnts_img.at<Vec2f>(i)[1]);
	}


	double max_dist = 0; double min_dist = 500;

	//-- Quick calculation of max and min distances between keypoints
	for( int i = 0; i < matches.size(); i++ )
	{	match = matches[i];
		float dist = match.distance;
		if( dist < min_dist ) min_dist = dist;
		if( dist > max_dist ) max_dist = dist;
	}
	
	cout << "max_dist = " << max_dist << endl;
	cout << "min_dist = " << min_dist << endl;

	// find the good matches
	/*
	//-- Draw only "good" matches (i.e. whose distance is less than 3*min_dist )
	std::vector< DMatch > good_matches;

	for( int i = 0; i < descriptors_object.rows; i++ )
	{ if( matches[i].distance < 3*min_dist )
	{ good_matches.push_back( matches[i]); }
	}
	*/

	//Mat funda = findFundamentalMat(matched_pnts_obj, matched_pnts_img, noArray(), CV_FM_8POINT);  -> can't work
	//Mat funda = findFundamentalMat(matched_pnts_obj, matched_pnts_img, noArray, FM_RANSAC, 3, 0.8); -> can't work
	//Mat funda =	findFundamentalMat(matched_pnts_obj, matched_pnts_img, FM_RANSAC, 3, 0.99);   // WORK!!!
	
	//MATmtxdisp(funda);

	// find homography transformation
	Mat H_RS = findHomography(matched_pnts_obj, matched_pnts_img, mask, CV_FM_RANSAC, 0.1);
	// compute transformation matrix    
	//Mat H = getPerspectiveTransform(matched_pnts_obj, matched_pnts_img);
	
	//MatInfo(matched_pnts_obj);
	//MatInfo(matched_pnts_img);
	MATmtxdisp(H_RS);
	//MATmtxdisp(H);
	MATmtxdisp(mask);
	MatInfo(mask);

	waitKey(0);


    return 0;
}