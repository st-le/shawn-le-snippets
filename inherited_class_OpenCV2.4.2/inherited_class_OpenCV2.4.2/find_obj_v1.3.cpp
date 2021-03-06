// v1.0 24/09/12 my version, using v2.4 feature classes in nonfree, finish constructor & extracting features
// v1.2 24/09/12 matching features
// v1.3 25/09/12 matching features using Descriptor Matcher of OpenCV

/*
 * A Demo to OpenCV Implementation of SURF
 * Further Information Refer to "SURF: Speed-Up Robust Feature"
 * Author: Liu Liu
 * liuliu.1987+opencv@gmail.com
 */
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/features2d.hpp"     // SURF & SIFT headers have been moved here!!!!
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc_c.h"

#include <iostream>
#include <vector>
#include <stdio.h>

#include "MatWork.hpp"

using namespace std;
using namespace cv;

void help()
{
    printf(
        "This program demonstrated the use of the SURF Detector and Descriptor using\n"
        "either FLANN (fast approx nearst neighbor classification) or brute force matching\n"
        "on planar objects.\n"
        "Usage:\n"
        "./find_obj <object_filename> <scene_filename>, default is box.png  and box_in_scene.png\n\n");
    return;
}

// define whether to use approximate nearest-neighbor search
#define USE_FLANN


/*
IplImage* image = 0;

double compareSURFDescriptors( const float* d1, const float* d2, double best, int length )
{
    double total_cost = 0;
    assert( length % 4 == 0 );
    for( int i = 0; i < length; i += 4 )
    {
        double t0 = d1[i  ] - d2[i  ];
        double t1 = d1[i+1] - d2[i+1];
        double t2 = d1[i+2] - d2[i+2];
        double t3 = d1[i+3] - d2[i+3];
        total_cost += t0*t0 + t1*t1 + t2*t2 + t3*t3;
        if( total_cost > best )
            break;
    }
    return total_cost;
}


int naiveNearestNeighbor( const float* vec, int laplacian,
                      const CvSeq* model_keypoints,
                      const CvSeq* model_descriptors )
{
    int length = (int)(model_descriptors->elem_size/sizeof(float));
    int i, neighbor = -1;
    double d, dist1 = 1e6, dist2 = 1e6;
    CvSeqReader reader, kreader;
    cvStartReadSeq( model_keypoints, &kreader, 0 );
    cvStartReadSeq( model_descriptors, &reader, 0 );

    for( i = 0; i < model_descriptors->total; i++ )
    {
        const CvSURFPoint* kp = (const CvSURFPoint*)kreader.ptr;
        const float* mvec = (const float*)reader.ptr;
    	CV_NEXT_SEQ_ELEM( kreader.seq->elem_size, kreader );
        CV_NEXT_SEQ_ELEM( reader.seq->elem_size, reader );
        if( laplacian != kp->laplacian )
            continue;
        d = compareSURFDescriptors( vec, mvec, dist2, length );
        if( d < dist1 )
        {
            dist2 = dist1;
            dist1 = d;
            neighbor = i;
        }
        else if ( d < dist2 )
            dist2 = d;
    }
    if ( dist1 < 0.6*dist2 )
        return neighbor;
    return -1;
}


int naiveNearestNeighbor( const float* vec, int laplacian,
						 const CvSeq* model_keypoints,
						 const CvSeq* model_descriptors )
{
	int length = (int)(model_descriptors->elem_size/sizeof(float));
	int i, neighbor = -1;
	double d, dist1 = 1e6, dist2 = 1e6;
	CvSeqReader reader, kreader;
	cvStartReadSeq( model_keypoints, &kreader, 0 );
	cvStartReadSeq( model_descriptors, &reader, 0 );

	for( i = 0; i < model_descriptors->total; i++ )
	{
		const CvSURFPoint* kp = (const CvSURFPoint*)kreader.ptr;
		const float* mvec = (const float*)reader.ptr;
		CV_NEXT_SEQ_ELEM( kreader.seq->elem_size, kreader );
		CV_NEXT_SEQ_ELEM( reader.seq->elem_size, reader );

		if( laplacian != kp->laplacian )
			continue;
		d = compareSURFDescriptors( vec, mvec, dist2, length );
		if( d < dist1 )
		{
			dist2 = dist1;
			dist1 = d;
			neighbor = i;
		}
		else if ( d < dist2 )
			dist2 = d;
	}
	if ( dist1 < 0.6*dist2 )
		return neighbor;
	return -1;
}


void findPairs( const CvSeq* objectKeypoints, const CvSeq* objectDescriptors,
           const CvSeq* imageKeypoints, const CvSeq* imageDescriptors, vector<int>& ptpairs )
{
    int i;
    CvSeqReader reader, kreader;
    cvStartReadSeq( objectKeypoints, &kreader );
    cvStartReadSeq( objectDescriptors, &reader );
    ptpairs.clear();

    for( i = 0; i < objectDescriptors->total; i++ )
    {
        const CvSURFPoint* kp = (const CvSURFPoint*)kreader.ptr;
        const float* descriptor = (const float*)reader.ptr;
        CV_NEXT_SEQ_ELEM( kreader.seq->elem_size, kreader );  // obj ele keypoint reader
        CV_NEXT_SEQ_ELEM( reader.seq->elem_size, reader );    // obj ele descriptor reader

        int nearest_neighbor = naiveNearestNeighbor( descriptor, kp->laplacian, imageKeypoints, imageDescriptors );

        if( nearest_neighbor >= 0 )
        {
            ptpairs.push_back(i);
            ptpairs.push_back(nearest_neighbor);
        }
    }
}


void findPairs( const vector<KeyPoint>& objectKeypoints, const Mat& objectDescriptors,
			   const vector<KeyPoint>& imageKeypoints, const Mat& imageDescriptors, vector<int>& ptpairs )
{
	int i;	

//	ptpairs = Mat::zeros(1, objectKeypoints.size(), CV_16UC);

	for( i = 0; i < objectDescriptors->total; i++ )
	{
		// get keypoint.laplacian
		KeyPoint kp = objectKeypoints[i];
		float descriptor = objectDescriptors.at<float>(kp.pt.y, kp.pt.x);


		//int nearest_neighbor = naiveNearestNeighbor( descriptor, kp, imageKeypoints, imageDescriptors ); // dunno what to pass

		if( nearest_neighbor >= 0 )
		{
			ptpairs.push_back(i);
			ptpairs.push_back(nearest_neighbor);
		}
	}
}

*/


/*
void
flannFindPairs( const CvSeq*, const CvSeq* objectDescriptors,
           const CvSeq*, const CvSeq* imageDescriptors, vector<int>& ptpairs )
{
	int length = (int)(objectDescriptors->elem_size/sizeof(float));

    cv::Mat m_object(objectDescriptors->total, length, CV_32F);
	cv::Mat m_image(imageDescriptors->total, length, CV_32F);


	// copy descriptors
    CvSeqReader obj_reader;
	float* obj_ptr = m_object.ptr<float>(0);
    cvStartReadSeq( objectDescriptors, &obj_reader );
    for(int i = 0; i < objectDescriptors->total; i++ )
    {
        const float* descriptor = (const float*)obj_reader.ptr;
        CV_NEXT_SEQ_ELEM( obj_reader.seq->elem_size, obj_reader );
        memcpy(obj_ptr, descriptor, length*sizeof(float));
        obj_ptr += length;
    }
    CvSeqReader img_reader;
	float* img_ptr = m_image.ptr<float>(0);
    cvStartReadSeq( imageDescriptors, &img_reader );
    for(int i = 0; i < imageDescriptors->total; i++ )
    {
        const float* descriptor = (const float*)img_reader.ptr;
        CV_NEXT_SEQ_ELEM( img_reader.seq->elem_size, img_reader );
        memcpy(img_ptr, descriptor, length*sizeof(float));
        img_ptr += length;
    }

    // find nearest neighbors using FLANN
    cv::Mat m_indices(objectDescriptors->total, 2, CV_32S);
    cv::Mat m_dists(objectDescriptors->total, 2, CV_32F);
    cv::flann::Index flann_index(m_image, cv::flann::KDTreeIndexParams(4));  // using 4 randomized kdtrees
    flann_index.knnSearch(m_object, m_indices, m_dists, 2, cv::flann::SearchParams(64) ); // maximum number of leafs checked

    int* indices_ptr = m_indices.ptr<int>(0);
    float* dists_ptr = m_dists.ptr<float>(0);
    for (int i=0;i<m_indices.rows;++i) {
    	if (dists_ptr[2*i]<0.6*dists_ptr[2*i+1]) {
    		ptpairs.push_back(i);
    		ptpairs.push_back(indices_ptr[2*i]);
    	}
    }
}


/* a rough implementation for object location */
/*
int
locatePlanarObject( const CvSeq* objectKeypoints, const CvSeq* objectDescriptors,
                    const CvSeq* imageKeypoints, const CvSeq* imageDescriptors,
                    const CvPoint src_corners[4], CvPoint dst_corners[4] )
{
    double h[9];
    CvMat _h = cvMat(3, 3, CV_64F, h);
    vector<int> ptpairs;
    vector<CvPoint2D32f> pt1, pt2;
    CvMat _pt1, _pt2;
    int i, n;

#ifdef USE_FLANN
    flannFindPairs( objectKeypoints, objectDescriptors, imageKeypoints, imageDescriptors, ptpairs );
#else
    findPairs( objectKeypoints, objectDescriptors, imageKeypoints, imageDescriptors, ptpairs );
#endif

    n = (int)(ptpairs.size()/2);
    if( n < 4 )
        return 0;

    pt1.resize(n);
    pt2.resize(n);
    for( i = 0; i < n; i++ )
    {
        pt1[i] = ((CvSURFPoint*)cvGetSeqElem(objectKeypoints,ptpairs[i*2]))->pt;
        pt2[i] = ((CvSURFPoint*)cvGetSeqElem(imageKeypoints,ptpairs[i*2+1]))->pt;
    }

    _pt1 = cvMat(1, n, CV_32FC2, &pt1[0] );
    _pt2 = cvMat(1, n, CV_32FC2, &pt2[0] );
    if( !cvFindHomography( &_pt1, &_pt2, &_h, CV_RANSAC, 5 ))
        return 0;

    for( i = 0; i < 4; i++ )
    {
        double x = src_corners[i].x, y = src_corners[i].y;
        double Z = 1./(h[6]*x + h[7]*y + h[8]);
        double X = (h[0]*x + h[1]*y + h[2])*Z;
        double Y = (h[3]*x + h[4]*y + h[5])*Z;
        dst_corners[i] = cvPoint(cvRound(X), cvRound(Y));
    }

    return 1;
}

*/

int main(int argc, char** argv)
{

	Mat img = imread("box.png", 0);
	Mat img1 = imread("box_in_scene.png", 0);
	char *org_wind = "the box";
	char *scene_wind = "box in scene";


	SIFT SIFTdect_obj = SIFT(100, 3, 0.04, 10, 1.6);
	SIFT SIFTdect_img = SIFT(100, 3, 0.04, 10, 1.6);

	vector<KeyPoint> keypoints_obj, keypoints_img;
	Mat descriptors_obj, descriptors_img; 

	
	SIFTdect_obj(img, noArray(), keypoints_obj, descriptors_obj, false);  // noArray(): using no mask
	SIFTdect_img(img1, noArray(), keypoints_img, descriptors_img, false);

	/*
	MatInfo(descriptors_obj);
	getchar();
	MATmtxdisp(descriptors_obj);
	getchar();
	*/

	Mat pnts_obj = Mat::zeros(1, keypoints_obj.size(), CV_32FC2);
	Mat pnts_img = Mat::zeros(1, keypoints_img.size(), CV_32FC2);
	
	for (int i = 0; i < keypoints_obj.size() ; i++)
	{
		printf("(%0.2f, %0.2f)\n", keypoints_obj[i].pt.x, keypoints_obj[i].pt.y);
		pnts_obj.at<Vec2f>(i)[0] = keypoints_obj[i].pt.x;
		pnts_obj.at<Vec2f>(i)[1] = keypoints_obj[i].pt.y;
	}
	
	for (int i = 0; i < keypoints_img.size() ; i++)
	{
		printf("(%0.2f, %0.2f)\n", keypoints_img[i].pt.x, keypoints_img[i].pt.y);
		pnts_img.at<Vec2f>(i)[0] = keypoints_img[i].pt.x;
		pnts_img.at<Vec2f>(i)[1] = keypoints_img[i].pt.y;
	}


	drawCircles(img, pnts_obj);
	drawCircles(img1, pnts_img);


	// Match keypoints with Brute Force Matcher
	BFMatcher kpMatcher(NORM_L2, false);

	vector<DMatch> matches;

	kpMatcher.match(descriptors_obj, descriptors_img, matches);   // no use mask -> skip the arg


	// Show results of matching
	Mat outimg;
	drawMatches(img, keypoints_obj, img1, keypoints_img, matches, outimg);
	
	cout << "Number of matches = " << matches.size() << endl;

	//imshow(org_wind, img);
	//imshow(scene_wind, img1);
	imshow("Match result", outimg);

	waitKey(0);


    return 0;
}