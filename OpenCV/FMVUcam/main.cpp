#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/video/background_segm.hpp"
#include <stdio.h>
#include <string>

#include <cstdio>
#include <iostream>
#include <fstream>

#include "OpenCV/MatWork.hpp"

#include "FMVUcam.h"

using namespace cv;
using namespace std;

int main( int /* argc */, char* /* argv[] */ )
{	

	/*struct _timeb   timeStart;
	struct _timeb   timeFinish;

	_ftime( &timeStart );*/


	//_ftime( &timeFinish );

//#ifdef WIN64
//	__time64_t uiTime = 
//#else
//	unsigned int uiTime = 
//#endif
//		( timeFinish.time * 1000 + timeFinish.millitm ) - 
//		( timeStart.time * 1000 + timeStart.millitm );
//
//	printf( 
//		"It took %ums to grab %u images. (%ums per image)\n\n", 
//		uiTime,
//		_IMAGES_TO_GRAB,
//		uiTime / _IMAGES_TO_GRAB );

	
	

	//
	// Save the raw image to disk.
	//
	/*printf( "Saving raw image.\n\n" );
	error = flycaptureSaveImage(
		context,
		&image,
		FILENAME_RAW,
		FLYCAPTURE_FILEFORMAT_PNG );
	_HANDLE_ERROR( error, "flycaptureSaveImage()" );   */

	FMVUcam cam;

	Mat image;
	/*cam.getframe(image);

	imshow("FlyCap Frame", image);
	waitKey(0);*/

	while (1)
	{
		//bb2.getframe(rawframe, recframe, dispframe);

		cam.getframe(image);
		
		imshow("FlyCap Frame",image);
		/*imshow("stereo raw image",rawframe);
		imshow("stereo rectified image",recframe);
		imshow("stereo disparity image",dispframe);*/

		char c = waitKey(1);

		if (c==27) break;
	}

	getchar();

	return 0;
}
