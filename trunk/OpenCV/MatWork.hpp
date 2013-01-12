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

void drawCircles(cv::Mat& image, const cv::Mat points, cv::Scalar color);

void drawCircles(cv::Mat& image, const cv::Mat points);

void drawSquares(cv::Mat& image, const cv::Mat points);


#endif