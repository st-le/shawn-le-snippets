#ifndef __FOLDERSPARSER_H__
#define __FOLDERSPARSER_H__

#include "opencv2/objdetect/objdetect.hpp"
//#include "opencv2/features2d/features2d.hpp"
//#include "opencv2/nonfree/features2d.hpp"     // SURF & SIFT headers have been moved here!!!!
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc_c.h"

#include <iostream>
#include <vector>
#include <stdio.h>

#include "global.h"

#include "OpenCV/MatWork.hpp"
#include "TextStream/TextReadWrite/TextWork.h"


int getImageList(char dir[FULLNAME_SZ], const std::vector<std::string> name_arr, std::vector<cv::Mat>& image_arr);


int FolderSparser(char Directory[FULLNAME_SZ], char FileList[NAME_SZ],
				  std::vector<cv::Mat>& received_img);

#endif


