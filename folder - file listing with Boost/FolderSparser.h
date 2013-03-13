#ifndef __FOLDERSPARSER_H__
#define __FOLDERSPARSER_H__

#ifndef BOOST_ALL_NO_LIB
#define BOOST_ALL_NO_LIB

//#include "opencv2/objdetect/objdetect.hpp"
//#include "opencv2/features2d/features2d.hpp"
//#include "opencv2/nonfree/features2d.hpp"     // SURF & SIFT headers have been moved here!!!!
#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc_c.h"

#include <boost/filesystem.hpp>

//#include <windows.h>
#include <iostream>
#include <vector>
#include <stdio.h>

//#include "global.h"

#include "OpenCV/MatWork.hpp"
#include "TextStream/TextReadWrite/TextWork.h"


//int getImageList(char dir[FULLNAME_SZ], const std::vector<std::string> name_arr, std::vector<cv::Mat>& image_arr);


//int FolderSparser(char Directory[FULLNAME_SZ], char FileList[NAME_SZ],
//				  std::vector<cv::Mat>& received_img);

//int FolderSparser(char Directory[FULLNAME_SZ],
//				  std::vector<cv::Mat>& received_img);

int GetImageinDir(const char* Dir,
				  std::vector<cv::Mat>& received_img);

void ListDirRec(const char *s, std::vector<std::string>& DirFileList, const char* ext);

#endif
#endif