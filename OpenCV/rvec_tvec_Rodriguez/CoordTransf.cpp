#include "CoordTransf.hpp"

using namespace cv;
using namespace std;


Mat skew(const Mat v)
{

	Mat sk = Mat::zeros(3, 3, CV_64FC1);
	double v1 = v.at<double>(0);
	double v2 = v.at<double>(1);
	double v3 = v.at<double>(2);

	sk.at<double>(0,1) = -v3;
	sk.at<double>(0,2) = v2;
	sk.at<double>(1,0) = v3;
	sk.at<double>(1,2) = -v1;
	sk.at<double>(2,0) = -v2;
	sk.at<double>(2,1) = v1;

	return sk;
}



cv::Mat RT2Hom(cv::Mat rot, cv::Mat trans)
{
	Mat T = Mat::eye(4, 4, CV_64FC1);

	//cout << "input to RT2Hom" << endl;
	//cout << rot << endl;
	//cout << trans << endl;

	//T(Range(0,3), Range(0,3)) = rot;    // why not work?
	//T(Range(0,3), Range(3,4)) = trans;  // why not work?
	rot.copyTo(T(Range(0,3), Range(0,3)));
	trans.copyTo(T(Range(0,3), Range(3,4)));

	cout << T << endl;

	return T;
}


cv::Mat invHom(cv::Mat T)
{
	Mat invT = Mat::eye(4, 4, CV_64FC1);
	Mat rot = T(Range(0,3), Range(0,3));
	Mat trans = T(Range(0,3), Range(3,4));

	invT(Range(0,3), Range(0,3)) = rot.t();
	invT(Range(0,3), Range(3,4)) = -rot.t()*trans;

	return invT;
}



Mat rotx(double fi)
{

	Mat Rx = Mat::eye(4, 4, CV_64FC1);

	double cfi = cos(fi);
	double sfi = sin(fi);

	Rx.at<double>(0,0) = 1;
	Rx.at<double>(1,1) = cfi;
	Rx.at<double>(1,2) = -sfi;
	Rx.at<double>(2,1) = sfi;
	Rx.at<double>(2,2) = cfi;

	return Rx;
}

Mat roty(double fi)
{

	Mat Ry = Mat::eye(4, 4, CV_64FC1);

	double cfi = cos(fi);
	double sfi = sin(fi);

	Ry.at<double>(0,0) = cfi;
	Ry.at<double>(0,2) = sfi;
	Ry.at<double>(1,1) = 1;
	Ry.at<double>(2,0) = -sfi;
	Ry.at<double>(2,2) = cfi;

	return Ry;
}

Mat rotz(double fi)
{

	Mat Rz = Mat::eye(4, 4, CV_64FC1);

	double cfi = cos(fi);
	double sfi = sin(fi);

	Rz.at<double>(0,0) = cfi;
	Rz.at<double>(0,1) = -sfi;
	Rz.at<double>(1,0) = sfi;
	Rz.at<double>(1,1) = cfi;
	Rz.at<double>(2,2) = 1;

	return Rz;
}


Mat transl(Mat vec)
{
	Mat trans = Mat::eye(4, 4, CV_64F);
	
	trans.at<double>(0, 3) = vec.at<double>(0);
	trans.at<double>(1, 3) = vec.at<double>(1);
	trans.at<double>(2, 3) = vec.at<double>(2);

	return trans; 
}


Mat transl(double dx, double dy, double dz)
{
	Mat trans = Mat::eye(4, 4, CV_64F);
	
	trans.at<double>(0, 3) = dx;
	trans.at<double>(1, 3) = dy;
	trans.at<double>(2, 3) = dz;

	return trans; 
}

// Created 14/06/13
// Description: - Ref: Robotics Class Roll-Pitch-Yaw Calc from transform10.pdf
//				- given rotation matrix, output roll-pitch-yaw rotation standard angles
//				- equation is: R(alf, bet, gam) = R(z, gam)*R(y, bet)*R(x, alf)
int RPYsolve(const Mat rot, double& alf, double& bet, double& gam)
{
//	Mat tmp = rotz(CV_PI/2)*roty(CV_PI);

	double a31 = rot.at<double>(2, 0);
	double a32 = rot.at<double>(2, 1);
	double a33 = rot.at<double>(2, 2);
	double a21 = rot.at<double>(1, 0);
	double a11 = rot.at<double>(0, 0);

	/*double a31 = tmp.at<double>(2, 0);
	double a32 = tmp.at<double>(2, 1);
	double a33 = tmp.at<double>(2, 2);
	double a21 = tmp.at<double>(1, 0);
	double a11 = tmp.at<double>(0, 0);*/

	try
	{
		bet = asin(-a31);
		if (bet == CV_PI/2)
		{
			cout << "beta gets singular!!" << endl;
			getchar();
		}		

		alf = atan2(a32/cos(bet), a33/cos(bet));   // RISK singularity !!!
		gam = atan2(a21/cos(bet), a11/cos(bet));
	}
	catch (int e)
	{
		cout << "beta gets singular!!" << endl;
		getchar();
	}	

	return 1;
}
