// 01/03/13 v2.0 + interface and show the image with OpenCV
//               + use the class to grasp the frame and return in OpenCV Mat format
//=============================================================================
// Copyright ?2004 Point Grey Research, Inc. All Rights Reserved.
// 
// This software is the confidential and proprietary information of Point
// Grey Research, Inc. ("Confidential Information").  You shall not
// disclose such Confidential Information and shall use it only in
// accordance with the terms of the license agreement you entered into
// with Point Grey Research, Inc. (PGR).
// 
// PGR MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
// SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE, OR NON-INFRINGEMENT. PGR SHALL NOT BE LIABLE FOR ANY DAMAGES
// SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING
// THIS SOFTWARE OR ITS DERIVATIVES.
//=============================================================================
//=============================================================================
// $Id: grabstereo.cpp,v 1.9 2009/03/20 15:59:31 soowei Exp $
//=============================================================================
//=============================================================================
// grabstereo
//
// Gets input from the Digiclops/Bumblebee, and performs stereo processing
// to create a disparity image. A rectified image from the reference camera
// and the disparity image are both written out.
//
//=============================================================================

//=============================================================================
// System Includes
//=============================================================================
//#include <stdafx.h>
#include <stdio.h>
#include <stdlib.h>

//=============================================================================
// Project Includes
//=============================================================================
#include "BumbleBee2.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

int main( int /* argc */, char** /* argv */ )
{
	BumbleBee2 bb2;

	Mat frameRGB = Mat::zeros(5, 10, CV_8UC3);
	Mat frame3D;
	Mat rawframe, recframe, dispframe;

//	bb2.getframe(frame);

	while (1)
	{
		//bb2.getframe(rawframe, recframe, dispframe);

		bb2.getframe16(recframe, frameRGB, frame3D);
		
		imshow("stereo RGB image",frameRGB);
		/*imshow("stereo raw image",rawframe);
		imshow("stereo rectified image",recframe);
		imshow("stereo disparity image",dispframe);*/

		imshow("stereo 8bit rectified image",recframe);

		char c = waitKey(1);

		cout << frame3D.at<Vec3f>(120, 160)[2] << endl;

		if (c==27) break;
	}

   return 0;
}