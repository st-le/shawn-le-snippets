#ifndef __BKGND_H__
#define __BKGND_H__


#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/features2d/features2d.hpp"
//#include "opencv2/nonfree/features2d.hpp"     // SURF & SIFT headers have been moved here!!!!
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc_c.h"

#include <iostream>
#include <vector>
#include <stdio.h>

//#include "global.h"

#include "OpenCV/MatWork.hpp"



void refineSegments(const cv::Mat& img, cv::Mat& mask, cv::Mat& dst);

int callTrainingBkGnd(const cv::Mat background, 
					  cv::BackgroundSubtractorMOG& bgsubtractor, cv::Mat& bgmask);




#endif