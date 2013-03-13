#ifndef __BUMBLEBEE2_H__
#define __BUMBLEBEE2_H__

//=============================================================================
// Standard C++
//=============================================================================
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

//=============================================================================
// OpenCV Includes
//=============================================================================
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

//=============================================================================
// PGR Includes
//=============================================================================
#include "triclops.h"
#include "pgrflycapture.h"
#include "pgrflycapturestereo.h"
#include "pnmutils.h"

//
// Macro to check, report on, and handle Triclops API error codes.
//
#define _HANDLE_TRICLOPS_ERROR( description, error )	\
{ \
	if( error != TriclopsErrorOk ) \
   { \
   printf( \
   "*** Triclops Error '%s' at line %d :\n\t%s\n", \
   triclopsErrorToString( error ), \
   __LINE__, \
   description );	\
   printf( "Press any key to exit...\n" ); \
   getchar(); \
   exit( 1 ); \
   } \
} \

//
// Macro to check, report on, and handle Flycapture API error codes.
//
#define _HANDLE_FLYCAPTURE_ERROR( description, error )	\
{ \
	if( error != FLYCAPTURE_OK ) \
   { \
   printf( \
   "*** Flycapture Error '%s' at line %d :\n\t%s\n", \
   flycaptureErrorToString( error ), \
   __LINE__, \
   description );	\
   printf( "Press any key to exit...\n" ); \
   getchar(); \
   exit( 1 ); \
   } \
} \


class BumbleBee2
{
private:
	// don't put initialization in class declaration except static const elements

	TriclopsContext   triclops;
	TriclopsImage     disparityImage;    // different image type/class/format
	TriclopsImage     refImage;
	TriclopsInput     triclopsInput;

	// 16bit var
	TriclopsInput       stereoData;
	TriclopsInput       colorData;
	TriclopsImage16		depthImage16;  
	TriclopsColorImage  colorImage; // = {0};
	TriclopsImage       monoImage; // = {0};

	unsigned char* rowIntColor;
	//unsigned char* rowIntMono;
	unsigned char* redColor; // = NULL;
	unsigned char* greenColor; // = NULL;
	unsigned char* blueColor; // = NULL;

	unsigned short*     row;
	// end of 16bit var

	FlyCaptureContext	   flycapture;
	FlyCaptureImage	   flycaptureImage;
	FlyCaptureInfoEx	   pInfo;
	FlyCapturePixelFormat   pixelFormat;

	TriclopsError     te;
	FlyCaptureError   fe;

	int iMaxCols;
	int iMaxRows;
	//int iMaxCols = 0;
	//int iMaxRows = 0;

	char* szCalFile;

	unsigned char* rowIntMono;   // common var

	unsigned char* redMono;
	unsigned char* greenMono;
	unsigned char* blueMono;

	// functions
	void BumbleBee2::DeleteBuffer();


public:

	BumbleBee2();

	~BumbleBee2();

	//void getframe(cv::Mat& frame);
	void getframe(cv::Mat& rawframe, cv::Mat& recframe, cv::Mat& dispframe);

	void getframe16(cv::Mat& recframe, cv::Mat& frameRGB, cv::Mat& frame3D);

	void Triclops2Mat(const TriclopsImage TriImg, cv::Mat& MatImg);

	void TrClpGetDepthImg(const TriclopsImage16 depthImage16, cv::Mat& depth_img);
	
};  // the comma here is a dangerous bug


#endif // BUMBLEBEE2_H