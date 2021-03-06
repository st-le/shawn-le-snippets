// testZhangOpenCV.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//#include <cv.h>
//#include <cxcore.h>
//#include <highgui.h>

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

#include <opencv/cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>

#include <vector>

using namespace cv;

// added const works for both cases i.e. CvMat* & const CvMat* -> pointee will not be affected
// 29/08/12: v3.0 -> can work with multi-channel CvMat (not easy with multi-channel)
//			 v3.2 -> multi-channel clean-up model
//			      -> predict bug: this only works for 1D array of multi-channel elements
// 30/08/12: bug found: if element type is not float, the reading crashes -> fixed type function
//                -> convert to Mat and display with MATmtxdisp function

void CvMatShow(const CvMat* mat)  
{
	uchar depth = 0;

	//printf("channel = %d", CV_MAT_CN(mat->type));
	depth = CV_MAT_CN(mat->type);

	if (depth <= 3)
	{
		float *data = mat->data.fl;  // 2nd method
		int n = mat->cols;

		printf("mat size (row, col) = (%d,%d)\n",depth,mat->cols);

		for( int i = 0; i < depth; i++ ){
			for( int j = 0; j < mat->cols; j++ )
			{				
				printf(" %14.8f",data[i*n+j]);  // 2nd method
			}
			printf("\n");
		}
	} else
		{
			printf("Num type is not supported!!!\n");		
		}
}

void editCvMat(CvMat* mat)
{
	 /* create missed variable matrix */
//	CV_MAT_ELEM(*mat,float,1,1) = 9999;  // 1st method -> access element (2,1) zero-based idx

	float *data = mat->data.fl;  // 2nd method -> access correctly element (2,2) zero-based idx
	int n = mat->cols;	
	data[2*n+2] = 9999;  	
}

int _tmain(int argc, _TCHAR* argv[])
{
	// initialize data

	// processing

	//int a[3][3] = {{1,2,3},{4,5,6},{7,8,9}};   
	float a[9] = {1,2,3,4,5,6,7,8,9};   

/*
	printf("first element of a = %0.2f",a+2]);  // cannot access array like this!!

	getchar();
*/

	// 1st test - create and pass a CvMat matrix to func
    CvMat matA = cvMat( 3, 3, CV_64F, a );
 
	CvMatShow(&matA);

	editCvMat(&matA);

	CvMatShow(&matA);

	getchar();

	// 2nd test
	CvMat matB = cvMat( 2, 3, CV_64F, a );     // this syntax works for CvMat
	CvMat matC = cvMat( 1, 3, CV_64F, a+6 );   // this syntax works for CvMat
 
	CvMatShow(&matB);
	CvMatShow(&matC);

	getchar();

	// 3rd test - cvCreateMat creates CvMat Header
	CvMat* rvec = cvCreateMat(1,3,CV_64F);   // use CvMat* or Ptr<CvMat>
	float *data = rvec->data.fl;  
	int n = rvec->cols;	
	data[0*n+0] = 9999;  
	data[0*n+1] = 1;  
	data[0*n+2] = 99;  

	CvMatShow(rvec);
	getchar();

	return 0;
}


