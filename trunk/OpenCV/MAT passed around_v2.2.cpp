// use for Mat matrix

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
using namespace cv;

/** Function Headers */

/** Global variables */

string window_name = "Color Segmentation";
  
float data[] = {1,2,3,4,5};

float data2D[2][4] = {{1,2,3,4},{7,8,9,10}};  // works OK

float data2D1[8] = {1,2,3,4,7,8,9,10};

int split(Mat frame, Mat ch1, Mat ch2, Mat ch3)
{

	for(int i = 0; i < frame.rows; i++)
		for(int j = 0; j < frame.cols; j++)
		{
			Vec3b ele = frame.at<Vec3b>(i,j);
			//			printf("ele (%d,%d) has chan1=%d, chan2=%d, chan3=%d\n",i,j, ele[0],ele[1],ele[2]);

			ch1.at<uchar>(i,j) = ele[0];
			ch2.at<uchar>(i,j) = ele[1];
			ch3.at<uchar>(i,j) = ele[2];
		}

	return 0;
}

//**********************************************//
//************** DISPLAY FUNCTIONS *************//
//**********************************************//

// v1.0 (07/05/12): assumed 1 channel MAT
// v1.2 (29/08/12): added 'const'
// v1.5			  : work with multi-chan Mat
//				  : predicted bug: only works with 1D array of multi-chan elements
// v2.0 (29/08/12): fix 1D array of multi-chan element bug
//				  : shortcoming : needs a fake var to identify element type
// v3.0 (30/08/12): probably no more bug but ugly output format

int MATmtxdisp(const Mat mtx)   // the shortest, most efficient but ugliest display
{	
	
	std::cout << mtx << " " << endl;
	
	return 0;
}

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

/*
Mat MatInit(Mat A)
{
	A = Mat(5,5, CV_32FC1);                // storage initialization

	// data init
	RNG().fill(A, RNG::UNIFORM, -20, 20);      

	//A = Mat::diag(Mat::ones(5,1,CV_32FC1)*CV_PI); // init diag. mtx
	//A = Mat::eye(B.rows, B.cols, CV_32FC1)*CV_PI;

	//A = Mat::ones(5,5,CV_32FC1)/CV_PI;       // multiply/divide by scalar made easy

	//A = Mat(1,3, CV_32FC1);
	//RNG().fill(A, RNG::UNIFORM, -20, 20);
	
	return A;
}
*/

int MatInit(Mat& A)           // how Mat is address referenced
{
//	A = Mat(5,5, CV_32FC1);                // storage initialization

	// data init
//	RNG().fill(A, RNG::UNIFORM, -20, 20);      

	//A = Mat(5,5,CV_32FC1, 5);

//	A = Mat(1, 5, CV_32FC1, &data, 2);   // init from float 1D - array
	A = Mat(2, 4, CV_32F, data2D1);     //  init from 2D - array

	// converts old-style CvMat to the new matrix; the data is not copied by default
	//Mat(const CvMat* m, bool copyData=false);
	// converts old-style IplImage to the new matrix; the data is not copied by default
	//Mat(const IplImage* img, bool copyData=false);
	// builds matrix from std::vector with or without copying the data
	//template<typename _Tp> explicit Mat(const vector<_Tp>& vec, bool copyData=false);


	//A = Mat::diag(Mat::ones(5,1,CV_32FC1)*CV_PI); // init diag. mtx
	//A = Mat::eye(B.rows, B.cols, CV_32FC1)*CV_PI;

	//A = Mat(1,3, CV_32FC1);

	return 0;
}



int MatAccess()
{
	Mat A, B;

	MatInit(A);
	//MatInit(B);

	//B = A.diag(0);							// get diagonal
	//Mat row = A.row(2);						// get row i 
	// Mat subMat = A(Range(0,2),Range(0,2));   // get subMat
	// A = Mat(A, cvRect(2,2,2,2));
	
	printf("Mat A\n");
	MATmtxdisp(A);
	printf("(2:2,2:2) range of A\n");
	MATmtxdisp(Mat(A, cvRect(2,2,2,2)));
	printf("row 3 of A\n");
	MATmtxdisp(A.row(3));
	printf("row 3,4,5 of A\n");
	MATmtxdisp(A.rowRange(Range(3,5)));           // don't show enuf 3 rows
	printf("col 3,4,5 of A\n");
	MATmtxdisp(A.colRange(Range(3,5)));
	//printf("Mat B\n");
	//printf("\n");
	//MATmtxdisp(B);
	
	return 0;
}


int Matmath()
{
	Mat A, B;

	MatInit(A);
	MatInit(B);

	
	MATmtxdisp(A*B.t());                     // dot product 1
	printf("\n");
	MATmtxdisp(A.t()*B);                     // dot product 2
	printf("\n");


	printf("dot product = %0.2f",A.dot(B));        // dot product 3 returns double type
	printf("\n");
	//printf("cross product = %0.2f",A.cross(B));        
	MATmtxdisp(A.cross(B));                   // cross product
	//MATmtxdisp(A.t());                     // transpose
	// cost = norm(cur, SOL.row(i), NORM_L1);  // norm 

	return 0;
}
int CutChanFrame(Mat frame, int chan)
{

	for(int i = 0; i < frame.rows; i++)
		for(int j = 0; j < frame.cols; j++)
		{
			frame.at<Vec3b>(i,j)[chan] = 2;			
		}

	return 0;
}


int test1(Mat& a)
{
	a = a*CV_PI;

	return 1;
}

int test(Mat& a)
{

	test1(a);

	return 0;
}

void testMatWork()
{
	Mat frame = imread("cow.jpg", 1);

	Vec3b a = frame.at<Vec3b>(1,1);

	Mat mt = Mat(4, 6, CV_32FC1, 1);

	Mat mtC3 = Mat(3, 5, CV_32FC3, CV_PI);

	//test(mt);

	//printf("%d",a[1]);

	//	printf("%0.2f\n",mt.at<float>(3,3));

	printf("%d\n",mtC3.channels());   // easy to get chan info

	printf("%0.2f\n",mtC3.at<Vec3f>(2,3)[2]);   // easy to access element

	Mat test_mtx;

	MatInit(test_mtx);

	MATmtxdisp(test_mtx);

	MATmtxdisp(mt);


	MATmtxdisp(mtC3);

	getchar();
}


void IplImageVSMat()
{
	IplImage* img = cvLoadImage("cow.jpg", 1);

	Mat imgMat(img);

	//cvShowImage("my cow",img);

	//cvWaitKey();

	imshow("my cow", imgMat);

	waitKey();

	//Mat frame = imread("cow.jpg", 1);
}


void CvMatVSMat()
{
	Mat imgMat = imread("cow.jpg", 1);
	CvMat imgCvMat = imgMat;    // Mat to CvMat
	Mat mtx = Mat(&imgCvMat, true);
	MATmtxdisp(mtx);
	getchar();

	//CvMatShow(&imgCvMat);
	//getchar();
	//cvShowImage("my cow",imgCvMat);
	//	cvWaitKey();

	/*
	float a[24] = {3.14, 3.14, 3.14, 3.14, 3.14, 3.14,
					3.14, 3.14, 3.14, 3.14, 3.14, 3.14,
					3.14, 3.14, 3.14, 3.14, 3.14, 3.14,
					3.14, 3.14, 3.14, 3.14, 3.14, 3.14};
	CvMat cvmat = cvMat(4,6, CV_32F, a);
	Mat imgMat = Mat(&cvmat, false);  // CvMat to Mat
	MATmtxdisp(imgMat);
	getchar();
	*/
}


void MatrixConversion()
{
	//IplImageVSMat();

	CvMatVSMat();

	

}
/** @function main */
int main( int argc, const char** argv )
{
	//testMatWork();
	
	MatrixConversion();

	return 0;
}
