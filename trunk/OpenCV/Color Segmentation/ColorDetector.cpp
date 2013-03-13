
#include "ColorDetector.h"

using namespace  std;
using namespace cv;

ColorDetector::ColorDetector(const Point3i inp_sample, double threshold)
{

	SampleUpdate(inp_sample);    // be careful with this i.e. there'll be no update!!!
	ThresholdUpdate(threshold);
}

ColorDetector::~ColorDetector()
{

}

void ColorDetector::Segment(const Mat frame, Mat& frame_segm)
{
	// Mat to IplImage
	//IplImage(frame);

	// Call EleWiseNorm
	Mat tmp_img;
	frame.copyTo(tmp_img);
	//EleWiseNorm(&IplImage(tmp_img), thres);  // this conversion works really well
	EleWiseNorm(tmp_img, thres);  // this conversion works really well

	// IplImage to Mat & return output
	tmp_img.copyTo(frame_segm);
}

void ColorDetector::ThresholdUpdate(double threshold)
{
	thres = threshold;
}

void ColorDetector::SampleUpdate(const Point3i inp_sample)
{
	sample.x = inp_sample.x;
	sample.y = inp_sample.y;
	sample.z = inp_sample.z;
}


int ColorDetector::EleWiseNorm(Mat& img, double thres)//int EleWiseNorm(IplImage* frame, cv::Mat normMtx)
{

	//imshow("received image", img);

	// Good in Color Segmentation but still suffers from illumination
	uchar ch1,ch2, ch3;	

	int det_cnt = 0;

	for(int i = 0; i < img.rows; i++)
		for(int j = 0; j < img.cols; j++)
		{

			ch1 = img.at<Vec3b>(i,j)[0];
			ch2 = img.at<Vec3b>(i,j)[1];
			ch3 = img.at<Vec3b>(i,j)[2];

			int dltx, dlty, dltz; 

			dltx = ch1 - sample.x;
			dlty = ch2 - sample.y;
			dltz = ch3 - sample.z;

			// L2
			//double dist = std::sqrt(dltx*dltx + dlty*dlty + dltz*dltz);
			// calculate L1
			//double dist = dltx*dltx + dlty*dlty + dltz*dltz;
			// calculate L0
			double dist = std::abs(dltx) + std::abs(dlty) + std::abs(dltz);

			//printf("%0.2f\n",dist);

			if (dist > thres)
			{
				img.at<Vec3b>(i,j)[0] = 0;
				img.at<Vec3b>(i,j)[1] = 0;
				img.at<Vec3b>(i,j)[2] = 0;	
			} else 
				det_cnt++;
		}

		return det_cnt;
}


int ColorDetector::EleWiseNorm(IplImage* img, double thres)//int EleWiseNorm(IplImage* frame, cv::Mat normMtx)
{

	imshow("received image", Mat(img));


	// Good in Color Segmentation but still suffers from illumination
	uchar ch1,ch2, ch3;	
 
	int det_cnt = 0;

	for(int i = 0; i < img->height; i++)
		for(int j = 0; j < img->width; j++)
		{

			ch1 = ((uchar*)(img->imageData + img->widthStep*i))[j*3 + 0];
			ch2 = ((uchar*)(img->imageData + img->widthStep*i))[j*3 + 1];
			ch3 = ((uchar*)(img->imageData + img->widthStep*i))[j*3 + 2];

			int dltx, dlty, dltz; 

			dltx = ch1 - sample.x;
			dlty = ch2 - sample.y;
			dltz = ch3 - sample.z;

			// L2
			//double dist = std::sqrt(dltx*dltx + dlty*dlty + dltz*dltz);
			// calculate L1
			//double dist = dltx*dltx + dlty*dlty + dltz*dltz;
			// calculate L0
			double dist = std::abs(dltx) + std::abs(dlty) + std::abs(dltz);

			//printf("%0.2f\n",dist);

			if (dist > thres)
			{
				((uchar*)(img->imageData + img->widthStep*i))[j*3 + 0] = 0;
				((uchar*)(img->imageData + img->widthStep*i))[j*3 + 1] = 0;
				((uchar*)(img->imageData + img->widthStep*i))[j*3 + 2] = 0;
			} else 
				det_cnt++;
		}

		return det_cnt;
}