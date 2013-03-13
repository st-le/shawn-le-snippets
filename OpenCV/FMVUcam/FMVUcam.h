#ifndef __FMVUCAM_H__
#define __FMVUCAM_H__


//=============================================================================
// System Includes
//=============================================================================
#include <assert.h>
#include <stdio.h>
#include <sys/timeb.h>
#include <memory.h>

//=============================================================================
// Project Includes
//=============================================================================
#include <pgrflycapture.h>

//=============================================================================
// OpenCV Includes
//=============================================================================
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

//=============================================================================
// Macro Definitions
//=============================================================================
//
// The number of images to grab.
//
#define _IMAGES_TO_GRAB 1; //10

//
// The maximum number of cameras on the bus.
//
#define _MAX_CAMS       32

//
// The index of the camera to grab from.
//
#define _CAMERA_INDEX   0

//
// What file format should we save the processed image as?
//
//#define SAVE_FORMAT     FLYCAPTURE_FILEFORMAT_PPM
#define SAVE_FORMAT     FLYCAPTURE_FILEFORMAT_JPG
//#define SAVE_FORMAT     FLYCAPTURE_FILEFORMAT_BMP

#define FILENAME_CONVERTED "converted.jpg"
//#define FILENAME_CONVERTED "converted.bmp"
#define FILENAME_RAW       "raw.pgm"

//
// Register defines
// 
#define INITIALIZE         0x000
#define CAMERA_POWER       0x610

//
// Helper code to handle a FlyCapture error.
//
#define _HANDLE_ERROR( error, function ) \
	if( error != FLYCAPTURE_OK ) \
   { \
   printf( "%s: %s\n", function, flycaptureErrorToString( error ) ); \
   } \
//return -1; \

class FMVUcam
{
private:

	// The Flycapture error. This should be assigned to the return value of 
	// most API functions and checked to ensure that the operation was completed
	// successfully.
	FlyCaptureError   error;

	// This acts as a handle to the camera.
	FlyCaptureContext context;   

	// Structure to store various information about the camera such as
	// model, serial number and DCAM compliance.
	FlyCaptureInfoEx info;

	//
	// Enumerate the cameras on the bus.
	//
	FlyCaptureInfoEx  arInfo[ _MAX_CAMS ];
	unsigned int	     uiSize;// = _MAX_CAMS;

	// image variable
	FlyCaptureImage image;
	FlyCaptureImage imageConverted;

	void FMVUcam::DeleteBuffer();

	void reportCameraInfo( const FlyCaptureInfoEx* pinfo );

public:

	FMVUcam();

	~FMVUcam();

	void getframe(cv::Mat& rawframe);

	void FlyCap2Mat(const FlyCaptureImage FCImg, cv::Mat& MatImg);

};

#endif  // FMVUCAM_H