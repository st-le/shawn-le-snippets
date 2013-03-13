#ifndef __COLOR_DETECTOR_H__
#define __COLOR_DETECTOR_H__

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc_c.h"

#include "OpenCV/MatWork.hpp"

class ColorDetector
{
private:
	// don't put initialization in class declaration except static const elements
	cv::Point3i sample;
	double thres;

	int EleWiseNorm(IplImage* img, double thres);//int EleWiseNorm(IplImage* frame, cv::Mat normMtx)

	int EleWiseNorm(cv::Mat& img, double thres);  // overloading with Mat

public:

	ColorDetector(const cv::Point3i inp_sample, double threshold);

	~ColorDetector();

	void SampleUpdate(const cv::Point3i inp_sample);

	void ThresholdUpdate(double threshold);

	void Segment(const cv::Mat frame, cv::Mat& frame_segm);

};  // the comma here is a dangerous bug


#endif