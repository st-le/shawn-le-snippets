// testZhangOpenCV.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"

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

// copied version
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

void showArray(float* arr, int size)
{

	for( int i = 0; i < size; i++ ){
		printf(" %0.2f",*arr);
		arr++;
	}
}

//int _tmain(int argc, _TCHAR* argv[])
int tmain()
{
	// initialize data

	// processing 

	//int a[3][3] = {{1,2,3},{4,5,6},{7,8,9}};   
	float a[9] = {1,2,3,4,5,6,7,8,9};   

    CvMat matA = cvMat( 3, 3, CV_64F, a );
 
	//CvMatShow(&matA);

	//editCvMat(&matA);

	//CvMatShow(&matA);

	//showArray(&a[0],9);  // changes in matA also affect the original float array a. This is what a header is about

	getchar();

	return 0;
}


