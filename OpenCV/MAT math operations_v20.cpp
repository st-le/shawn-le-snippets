// use for Mat matrix

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
using namespace cv;

/** Function Headers */

/** Global variables */

string window_name = "Color Segmentation";
  
//float data[] = {1,2,3,4,5};

//float data[2][5] = {{1,2,3,4,5},{7,8,9,10,11}};
float data[10] = {1,2,3,4,5,7,8,9,10,11};
//double data[10] = {1,2,3,4,5,7,8,9,10,11};


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

// v1.0 (07/05/12): assumed 1 channel MAT

int MATmtxdisp(Mat mtx)
{	float ele;

	for(int i = 0; i < mtx.rows; i++)
	{
		for(int j = 0; j < mtx.cols; j++)
		{
			//Vec3b ele = mtx.at<Vec3b>(i,j);
			ele = mtx.at<float>(i,j);
			//			printf("ele (%d,%d) has chan1=%d, chan2=%d, chan3=%d\n",i,j, ele[0],ele[1],ele[2]);
			printf("%8.2f",ele);
		}
		printf("\n");
	}

	return 0;
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

	//A = Mat(5,5,CV_32FC1, 5);    // filled Mat A with '5'

//	A = Mat(1, 5, CV_32FC1, &data, 2);   // init from float 1D - array
	A = Mat(2, 5, CV_32FC1, &data);     // this can be used to init from 2D - array to create 2D Mat

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
//	MATmtxdisp(Mat(A, cvRect(2,2,2,2)));
	printf("row 3 of A\n");
//	MATmtxdisp(A.row(3));
	printf("row 3,4,5 of A\n");
//	MATmtxdisp(A.rowRange(Range(3,5)));           // don't show enuf 3 rows
	printf("col 3,4,5 of A\n");
//	MATmtxdisp(A.colRange(Range(3,5)));
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

/** @function main */
int main( int argc, const char** argv )
{
	CvCapture* capture;
	Mat frame = imread("cow.jpg", 1);

	
	/*
	Point2f c;
	c.x = (float)frame.rows/2;
	c.y = (float)frame.cols/2;
	Mat rot = getRotationMatrix2D( c, -45, 1);

	Mat dst;
	Size size;
	size.height = frame.rows;
	size.width = frame.cols;
	warpAffine(frame, dst, rot, size, INTER_LINEAR, BORDER_DEFAULT, 0) ;
	*/

	// matrix para
	/*
	uchar* data_ptr = frame.data;

	printf("step = %d\n",frame.step[0]);

	uchar* pij = frame.data+frame.step[0]*10+frame.step[1]*30;

	printf("Pointer (%d,%d) = %d\n", 10, 30, *pij);
	pij++;
	printf("Pointer +1 (%d,%d) = %d\n", 10, 30, *pij);
	pij++;
	printf("Pointer +2 (%d,%d) = %d\n", 10, 30, *pij);

	Vec3b ele = frame.at<Vec3b>(10,30);

	printf("ele (%d,%d) has chan1=%d, chan2=%d, chan3=%d\n",10,30, ele[0],ele[1],ele[2]);

	printf("At method (%d,%d) = %d\n", 30, 10, frame.at<uchar>(30,10));


	printf("The %d-d matrix has %d rows & %d cols & depth=%d\n", frame.dims, frame.rows, frame.cols, frame.channels());

	printf("%d\n", *data_ptr);
	*/

//	printf("(%d,%d) = %d\n", 10, 30, frame.at<uchar>(10,30));

	// EOmtx para

	
	
//	p = frame.at<Point3i>(1,1);

	//Vec3b ele = frame.at<Vec3b>(1,1); 

	/*
	Mat ch1 = Mat(frame.rows, frame.cols, CV_8UC1);
	Mat ch2 = Mat(frame.rows, frame.cols, CV_8UC1);
	Mat ch3 = Mat(frame.rows, frame.cols, CV_8UC1);

	split(frame, ch1, ch2, ch3);
	CutChanFrame(frame,1);
	*/
	// EOMatrix Access

	// TEST MATRIX OPERATION

	// Mat Initialization
	//Mat A; 
	//MatInit(A);

	// Mat Access
	MatAccess();

	// Mat math operations
	//Matmath();

	// END TEST MATRIX OPERATION
	/*
	imshow(window_name, frame);
	imshow("channel 1", ch1);
	imshow("channel 2", ch2);
	imshow("channel 3", ch3);
	*/

	getchar();

	waitKey();

	return 0;
}
