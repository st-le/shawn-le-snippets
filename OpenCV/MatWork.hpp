#ifndef __MATWORK_HPP__
#define __MATWORK_HPP__

#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <vector>
#include <iostream>


typedef unsigned int uint;  // not use this one yet

void MatInfo(const cv::Mat matrix);

int MATmtxdisp(const cv::Mat mtx);

cv::Mat FindNonZero(const cv::Mat mtx);

// Selects subset_size random different points from [0, num_points - 1] range
void selectRandom(int subset_size, int num_points, std::vector<int>& subset);

// Template function to access OpenCV Mat
// Added 17/12/12 
// 12/01/13: added to header
template <class NumType>
void drawCircles(cv::Mat& image, const cv::Mat_<cv::Vec<NumType, 2>> points, cv::Scalar color)
{
	// fix format of Matrix <-> hard coding

	//MatInfo(points);
	//getchar();

	//CV_Assert(points.channels() == 2);
	//CV_Assert(points.depth() == CV_32FC2); // this is so restricted!!

	//CV_Assert(points.channels() == 2);
	//CV_Assert(points.depth() == CV_16UC2);

	// added working for both row/col point vector

	Point2d p0;

	for (int i = 0; i < points.cols; i++)
	{
		p0.x = cvRound(points.at<Vec<NumType, 2>>(0,i)[0]);
		p0.y = cvRound(points.at<Vec<NumType, 2>>(0,i)[1]);

		circle(image, p0, 5, color, 2, 8);
	}
}

void drawCircles(cv::Mat& image, const cv::Mat points, cv::Scalar color);

void drawCircles(cv::Mat& image, const cv::Mat points);

void drawSquares(cv::Mat& image, const cv::Mat points);


// Template function to copy data from 2D vector to 2D Mat
// Created 12/01/13
template <class NumType>
cv::Mat Vect2Mat(std::vector<std::vector<NumType>> vect)
{
	cv::Mat mtx = cv::Mat::zeros(vect.size(), vect[0].size(), cv::DataType<NumType>::type);  
	//Mat mtx;

	// copy data
	for (int i=0; i<vect.size(); i++)
		for (int j=0; j<vect[i].size(); j++)
		{
			mtx.at<NumType>(i,j) = vect[i][j];
			//cout << vect[i][j] << " ";
		}	

		return mtx;
}

#endif