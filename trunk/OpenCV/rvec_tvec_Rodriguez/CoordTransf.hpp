#ifndef __COORDTRANSF_HPP__
#define __COORDTRANSF_HPP__


#include "opencv2/objdetect/objdetect.hpp"
//#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/features2d.hpp"     // SURF & SIFT headers have been moved here!!!!
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc_c.h"

#include <iostream>
#include <vector>
#include <stdio.h>

//#include "OpenCV/MatWork.hpp"
//#include "MatWork.hpp"

cv::Mat skew(const cv::Mat v);

// rotation utilities, angle in Radian
cv::Mat rotx(double fi);
cv::Mat roty(double fi);
cv::Mat rotz(double fi);

cv::Mat RT2Hom(cv::Mat rot, cv::Mat trans);

cv::Mat invHom(cv::Mat T);

cv::Mat transl(double dx, double dy, double dz);

cv::Mat transl(cv::Mat vec);

int RPYsolve(const cv::Mat rot, double& alf, double& bet, double& gam);

#endif