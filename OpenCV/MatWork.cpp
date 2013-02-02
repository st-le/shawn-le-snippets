
#include "OpenCV/MatWork.hpp"

using namespace cv; 
using namespace std;


//**********************************************//
//************** MATRIX INFORMATIO *************//
//**********************************************//

// v1.0 (13/09/12):
void MatInfo(const Mat matrix)
{
	printf("### Matrix Properties ###\n");
	printf("rows = %d, cols = %d\n", matrix.rows, matrix.cols);
	printf("channels = %d\n", matrix.channels());
	printf("dims = %d\n", matrix.dims);
	printf("depth = %d\n", matrix.depth());
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


//**********************************************//
//************** RANDOM SUBSAMPLING*************//
//**********************************************//

// v1.0 (13/09/12): added to standard routines

// Selects subset_size random different points from [0, num_points - 1] range
void selectRandom(int subset_size, int num_points, vector<int>& subset)
{
	subset.resize(subset_size);
	for (int i = 0; i < subset_size; ++i)
	{
		bool was;
		do
		{
			subset[i] = rand() % num_points;
			was = false;
			for (int j = 0; j < i; ++j)
				if (subset[j] == subset[i])
				{
					was = true;
					break;
				}
		} while (was);
	}
}


//**********************************************//
//************** Find Non Zero Pxl *************//
//**********************************************//

// v1.0 (13/09/12): added to standard routines

// return non zero pixels of a 1channel uchar Mat
Mat FindNonZero(const Mat mtx)
{

	CV_Assert(mtx.channels() == 1);
	CV_Assert(mtx.depth() == CV_8UC1);    // assert this to define access type

	int nzcnt = countNonZero(mtx);

	Mat nzpxl = Mat(1, nzcnt, CV_32FC2, Scalar::all(0));

	int cnt = 0;

	for (int i = 0; i < mtx.rows; i++)
		for (int j = 0; j < mtx.cols; j++)
			if (mtx.at<uchar>(i,j) != 0)
			{
				nzpxl.at<Vec2f>(0, cnt)[0] = j;
				nzpxl.at<Vec2f>(0, cnt)[1] = i;
				cnt++;
			}	

	return nzpxl;
}


//**********************************************//
//************** Draw cirles on img*************//
//**********************************************//

// v1.0 (14/09/12): created

// draw circles from array of points
/*
template <class MatType>    // -> use function template to fix this generic
void drawCircles(Mat& image, const Mat points)
{
	// fix format of Matrix <-> hard coding

	//MatInfo(points);
	//getchar();

	//CV_Assert(points.channels() == 1);
	//CV_Assert(points.depth() == CV_32FC2); // this is so restricted!!

	// added working for both row/col point vector

	Point2d p0;

	for (int i = 0; i < points.cols; i++)
	{	
		p0.x = cvRound(points.at<Vec2f>(0,i)[0]);
		p0.y = cvRound(points.at<Vec2f>(0,i)[1]);

		circle(image, p0, 3, CV_RGB(255, 0, 0), 1, 8);
	}	
}
*/



void drawCircles(Mat& image, const Mat points, Scalar color)
{
	// fix format of Matrix <-> hard coding

	//MatInfo(points);
	//getchar();

	CV_Assert(points.channels() == 2);
	//CV_Assert(points.depth() == CV_32FC2); // this is so restricted!!

	//CV_Assert(points.channels() == 2);
	//CV_Assert(points.depth() == CV_16UC2); 

	// added working for both row/col point vector

	Point2d p0;

	for (int i = 0; i < points.cols; i++)
	{	
		//p0.x = cvRound(points.at<Vec2i>(0,i)[0]);
		//p0.y = cvRound(points.at<Vec2i>(0,i)[1]);

		p0.x = cvRound(points.at<Vec2f>(0,i)[0]);
		p0.y = cvRound(points.at<Vec2f>(0,i)[1]);

		//p0.x = cvRound(points.at<Vec2d>(0,i)[0]);
		//p0.y = cvRound(points.at<Vec2d>(0,i)[1]);

		circle(image, p0, 5, color, 2, 8);
	}
}


void drawCircles(Mat& image, const Mat points)
{
	// fix format of Matrix <-> hard coding
	
	//MatInfo(points);
	//getchar();

	CV_Assert(points.channels() == 2);
	//CV_Assert(points.depth() == CV_32FC2); // this is so restricted!!

	//CV_Assert(points.channels() == 2);
	//CV_Assert(points.depth() == CV_16UC2); 

	// added working for both row/col point vector

	Point2d p0;

	for (int i = 0; i < points.cols; i++)
	{	
		//p0.x = cvRound(points.at<Vec2i>(0,i)[0]);
		//p0.y = cvRound(points.at<Vec2i>(0,i)[1]);

		p0.x = cvRound(points.at<Vec2f>(0,i)[0]);
		p0.y = cvRound(points.at<Vec2f>(0,i)[1]);

		//p0.x = cvRound(points.at<Vec2d>(0,i)[0]);
		//p0.y = cvRound(points.at<Vec2d>(0,i)[1]);

		circle(image, p0, 5, CV_RGB(255, 255, 0), 2, 8);
	}
}



//***********************************************//
//************** Draw squares on img*************//
//***********************************************//

// v1.0 (20/09/12): created

// draw squares from array of points

void drawSquares(Mat& image, const Mat points)
{
	// fix format of Matrix <-> hard coding

	//MatInfo(points);
	//getchar();
/*
	Mat points;

	if (points0.depth() == CV_32FC1)
	{
		points0.convertTo(points, CV_64FC1);
	}
*/


//	if (points.rows() > points.cols)      // write for both row & column matrix
//		Reshape()

	MatInfo(points);
	MATmtxdisp(points);
	//getchar();


	CV_Assert(points.channels() == 2);
	CV_Assert(points.depth() == CV_32FC1);

	// added working for both row/col point vector

	Point2d p0, p1;

	int size = 4;

	for (int i = 0; i < points.cols; i++)
	{	
		p0.x = cvRound(points.at<Vec2f>(i)[0] - size);
		p0.y = cvRound(points.at<Vec2f>(i)[1] - size);

		p1.x = cvRound(points.at<Vec2f>(i)[0] + size);
		p1.y = cvRound(points.at<Vec2f>(i)[1] + size);

		rectangle(image, p0, p1, CV_RGB(255, 0, 0), 1, 8);
	}	
}