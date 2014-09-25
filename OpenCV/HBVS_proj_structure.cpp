// ***** Visual_servoing
// v1.0 24/09/12 my version, using v2.4 feature classes in nonfree, finish constructor & extracting features
// v1.2 24/09/12 matching features
// v1.3 25/09/12 matching features using Descriptor Matcher of OpenCV i.e. BFmatcher
// v1.5 23/01/13 use equalizeHist and adaptivethres to preprocess image
// v2.2 23/01/13 add offsets to model image and choose the best match -> FAIL!!!
//				-> effect of brightness (light source) is not simply increasing pixel value
// v3.0 24/01/13 use the database more efficiently -> object is matched with features from different images in db
// v3.1 24/01/13 transitory version


#include "opencv2/objdetect/objdetect.hpp"
//#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/features2d.hpp"     // SURF & SIFT headers have been moved here!!!!
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc_c.h"

#include <iostream>
#include <vector>
#include <stdio.h>
#include <time.h>

#include "global.h"

#include "MatWork.hpp"
#include "TextWork.h"

#include "createDB.h"
#include "bkgnd_segm.h"
#include "ObjectDetector.hpp"
#include "ZhangPoseEstimator.hpp"
#include "VisualServoing.hpp"
#include "CameraDS.h"
#include "BumbleBee2.h"
#include "TableTopFunc.h"
#include "DENSOrobot.hpp"

using namespace std;
using namespace cv;

//const int sample_sz = 200;
const float sample_pc = 0.5;
const int tol = 25;

char Testdir[FULLNAME_SZ] = "D:/WORK/WORK/NTUST/projects/Visual Studio 2008/Projects/WriteWC2Frames-use this one/WriteWC2Frames/Debug/greencart_closelook_scaled";

// ** database directories
char DBdir[FULLNAME_SZ] = "D:/WORK/WORK/NTUST/projects/Visual Studio 2008/Projects/OpenCV2.4.2/vision_for_IBVS/obj_grasp_detection/testSURF/grasp database";
char DBfilelist[NAME_SZ] = "filelist.txt";
char Testfilelist[NAME_SZ] = "filelist.txt";

int sample_sz;
Mat markerMask, img;
Rect selRegion, selRegion1;
Point prevPt(-1, -1);
int ObsIsSelected = 0;

int grasp_found = 0;

struct DSpose 
{
	double x, y, z, rol, pit, yal;		
};

void help()
{
    printf(
        "This program demonstrated the use of the SURF Detector and Descriptor using\n"
        "either FLANN (fast approx nearest neighbor classification) or brute force matching\n"
        "on planar objects.\n"
        "Usage:\n"
        "./find_obj <object_filename> <scene_filename>, default is box.png  and box_in_scene.png\n\n");
    return;
}


void NonZeroLocSearch(const Mat& img, Point2i& minloc, Point2i& maxloc)
{
	int min_row = img.rows;
	int max_row = 0;
	int min_col = img.cols;
	int max_col = 0;

	for (int i = 0; i < img.rows; i++)
		for (int j = 0; j < img.cols; j++)
			if (img.at<uchar>(i, j) != 0)
			{
				if (min_row > i) min_row = i;
				if (max_row < i) max_row = i;
				if (min_col > j) min_col = j;
				if (max_col < j) max_col = j;
			}
	
	minloc = Point2i(min_col, min_row);
	maxloc = Point2i(max_col, max_row);
}

static void onMouse( int event, int x, int y, int flags, void* )
{
	if( x < 0 || x >= img.cols || y < 0 || y >= img.rows )
		return;

	if( event == CV_EVENT_LBUTTONUP || !(flags & CV_EVENT_FLAG_LBUTTON) )
	{
		prevPt = Point(-1,-1);

		if (event == CV_EVENT_LBUTTONUP)   // detect mouse up event
		{
			printf("mouse is up\n");
			
			Point2i minloc, maxloc; 
			NonZeroLocSearch(markerMask, minloc, maxloc);

			//printf("min loc (%d, %d)\n", minloc.x, minloc.y);
			//printf("max loc (%d, %d)\n", maxloc.x, maxloc.y);
			selRegion = Rect(minloc.x, minloc.y, maxloc.x - minloc.x, maxloc.y - minloc.y);
			selRegion1 = Rect(minloc.x - tol, minloc.y - tol, maxloc.x - minloc.x + 2*tol, maxloc.y - minloc.y + 2*tol);
			//Mat imgSelReg;
			//cvtColor(markerMask, imgSelReg, CV_GRAY2BGR);
			//rectangle(imgSelReg, selRegion, Scalar(0, 255, 0), 3, 8);
			//imshow("Select result", imgSelReg);
			ObsIsSelected = 1;
		}
	}
	else if( event == CV_EVENT_LBUTTONDOWN )
		prevPt = Point(x,y);
	else if( event == CV_EVENT_MOUSEMOVE && (flags & CV_EVENT_FLAG_LBUTTON) )
	{

		Point pt(x, y);
		if( prevPt.x < 0 )
			prevPt = pt;
		line( markerMask, prevPt, pt, Scalar::all(255), 1, 8, 0 );
		line( img, prevPt, pt, Scalar::all(255), 5, 8, 0 );
		prevPt = pt;
		imshow("object selection", img);

		// mask image
		//imshow("mask image", markerMask);
		//MatInfo(markerMask);
	}
}

int MatOffset(Mat& inp, int os)
{
	
	// Only apply to grayscale image
	for (int i = 0; i < inp.rows; i++)
		for (int j = 0; j < inp.cols; j++)
			if (inp.at<uchar>(i,j) != 0)
			{
				inp.at<uchar>(i, j) = inp.at<uchar>(i, j) + os;
			}	

	return 1;
};


int main(int argc, char** argv)
{
	// CREATE FEATURE DATABASE
	//vector<KeyPoint> db_keypoints;
	//Mat db_descriptors;
	vector<vector<vector<KeyPoint>>> db_keypoints;
	vector<vector<Mat>> db_descriptors;

	vector<Mat> db_test_img;

	// input: db_FileList, DBdir, test_db_FileList, TestDir
	// output: db_keypoints, db_descriptors, test_db_img
	char tmpfullstr[FULLNAME_SZ], tmpfullstr1[FULLNAME_SZ];

	/*createDB(DBdir, DBfilelist, Testdir, Testfilelist,
		     db_keypoints, db_descriptors, 
			 test_db_img);*/

	vector<string> Objects; 
	/*Objects.push_back(string("bottle"));
	Objects.push_back(string("cart"));
	Objects.push_back(string("densemilk"));
	Objects.push_back(string("milkcan"));*/
	Objects.push_back(string("grasp1"));
	Objects.push_back(string("grasp2"));
	Objects.push_back(string("grasp3"));
	Objects.push_back(string("grasp4"));
	Objects.push_back(string("grasp5"));
	Objects.push_back(string("grasp6"));
	Objects.push_back(string("grasp7"));
	Objects.push_back(string("grasp8"));
	Objects.push_back(string("grasp9"));
	Objects.push_back(string("grasp10"));
	Objects.push_back(string("grasp11"));


	Mat ret_db_descriptors;
	//vector<Mat> test_db_img;
	vector<vector<Mat>> hier_db_img;
	createDB(DBdir, Testdir, Objects,
			 db_keypoints, db_descriptors, 
			 db_test_img, hier_db_img);

	cout << hier_db_img.size() << endl;

	//cout << << endl;

	// check database image read
	for (int i=0; i < hier_db_img.size(); i++)
		for (int j=0; j < hier_db_img[i].size(); j++)
		{
			cout << "Object is: " << Objects[i] << endl;
			imshow("read object", hier_db_img[i][j]);   // interaction is moved to main
			waitKey(1);
		}

	destroyWindow("read object");
    // Check detection of each image
	int id=0;
	grasp_found = 0;
	
	int vote;
	vector<KeyPoint> keypoints_img;
	vector<DMatch> enh_good_matches;

	ZhangPoseEstimator PoseEst;
	Mat rvec, tvec;
	Mat objPoints, imgPoints;

	// initialize 1st obj keypoint, descriptor
	vector<KeyPoint> keypoints_obj;
	Mat descriptor_obj, descriptor_img;
	SIFT SIFTdect = SIFT(400, 3, 0.05, 10, 1.6);
	SIFTdect(db_test_img[db_test_img.size()-1], noArray(), keypoints_obj, descriptor_obj, false);

	// timing control
	/*time_t tic, toc;
	time(&tic);*/

	clock_t tic_cv, toc_cv;
	tic_cv = clock();
	float t_cv;

	// #### DENSO control vars
	DENSOrobot DSrb = DENSOrobot(1);   // 1 to run real robot

	// Initial Joint Pose - always start from this pose
	Mat OrgPose = Mat::zeros(1, 6, CV_64F);
	//Mat OrgPose = Mat::zeros(1, 6, CV_64F, 0);   // WRONG SYNTAX!!!! init Mat with Mat::zeros
	Mat DstPose = Mat::zeros(1, 6, CV_64F);   // used later
	Mat OrgPoseJnt, traj;

	double OrgPose_ar1[6] = {0, -CV_PI/6, 2*CV_PI/3, 0, 0, CV_PI};
	OrgPose = Mat(1, 6, CV_64F, OrgPose_ar1);	
	OrgPose.copyTo(OrgPoseJnt);

	// update pose to DENSO robot
	DSrb.updateJPose(OrgPose);

	// fixed roll-pitch-yaw
	//vector<double> tmp_vect;
	//double rol=CV_PI/4, pit=CV_PI/4, yaw=CV_PI/4;   // fix roll-pitch-yaw
	double rol=0, pit=0, yaw=0;   // fix roll-pitch-yaw
	//double rol=0, pit=-CV_PI/2, yaw=0;   // fix roll-pitch-yaw
	//double rol=0, pit=-CV_PI/2, yaw=0;   // fix roll-pitch-yaw
	//double rol=0, pit=-CV_PI/4, yaw=0;   // fix roll-pitch-yaw

	Mat BestTraj;
	// ################################

	// #### START Visual Servoing vars
	VisualServoing VScaller;
	Mat VJacob, A_16;

	// Prepare DirectShow cam
	CCameraDS cam; 
	cam.OpenCamera(1);
	Mat frame;

	// flag to skip the 1st singular solution
	int flg = 0;

	//for (int i=0; i<db_test_img.size(); i++)
	//for (int i=db_test_img.size()-1; i>0; i--)   // iterate input frames
	int converge_flg = 0;
	double err_norm = 9999999;
	int demo = 0;
	int log_cnt = 0;
	// #### END Visual Servoing vars

	// ****** initial SETUP 
	Mat tmp = Mat::zeros(1,6,CV_64F);
	// ****** START Move to initial Pose
	// 0, -CV_PI/6, 2*CV_PI/3, 0, 0, 0
	tmp.at<double>(0) = 0;
	tmp.at<double>(1) = -CV_PI/6;
	tmp.at<double>(2) = 2*CV_PI/3;
	tmp.at<double>(3) = 0;
	tmp.at<double>(4) = 0;
	tmp.at<double>(5) = CV_PI;    // tmp here is 6x1 mat

	int ret = DSrb.JTrajPlanner(tmp);  // TrajPlanner works with row vector

	if (ret)
	{
		//MATmtxdisp(traj/CV_PI*180);
		//DstPose.copyTo(OrgPoseJnt);

		//getchar();
	}
	else 
	{
		printf("there is no good solution!!\n");
		//getchar();
		//return 1;
	}

	getchar();
	// ****** END Move to initial Pose


	// ******************************* Via point matrix -> this is old via point setup -> the new one is in "pattern with joint limit" project (28/06/13)
	vector<vector<double>> ViaPoint_vect;
	vector<double> tmp_vect;
	
	DSpose pose, pose1;
	vector<DSpose> poses_o, poses_b;
	double R = 120; //150; 200; 120 (to see all 2d pattern)
	double dfi = 0.17453292519943295769236907684886;//10/180*3.14159265358979;

	double A = 360; //440;
	double B = 720 - 410 - 70; //750 - 410 - 50; 720; // -50: 2d pattern is lower than the box

	// transformation from Object to Base (user/llv) - added 27/06/13
	Mat bTo = Mat::eye(4,4,CV_64F);
	/*bTo.at<double>(0,3) = A; 
	bTo.at<double>(1,3) = 0;
	bTo.at<double>(2,3) = B;*/
	tmp = trans(A,0,B)*rotz(CV_PI);
	tmp.copyTo(bTo);
	
	Mat oP, bP;

	// fi_x, fi_y range from -40 to 40 deg
	for (int i=-4; i<5; i++)        // yaw
		for (int j=-4; j<5; j++)    // pit
	{
		// x,y,z in mm
		pose.x = R*cos(j*dfi)*cos(i*dfi);
		pose.y = R*cos(j*dfi)*sin(i*dfi);
		pose.z = R*sin(j*dfi);
		pose.rol = CV_PI;		   // new RPY DS std 27/06/13 - reverse the wc 18/06/13
		pose.pit = j*dfi; //-j*dfi;     // this is RPY of ee (x5y5z5 int. coord.) already
		pose.yal = i*dfi; //-i*dfi;     // 
		/*pose.pit = -j*dfi;
		pose.yal = -i*dfi;*/

		poses_o.push_back(pose);
		
		// need only translation from Obj to Base (usr/llv)
		/*pose1.x = pose.x - A;
		pose1.y = pose.y;
		pose1.z = pose.z + B;
		pose1.rol = pose.rol;
		pose1.pit = pose.pit;
		pose1.yal = pose.yal;*/
		oP = Mat::ones(4,1,CV_64F);
		oP.at<double>(0) = pose.x;
		oP.at<double>(1) = pose.y;
		oP.at<double>(2) = pose.z;
		bP = bTo*oP;
		pose1.x = bP.at<double>(0);
		pose1.y = bP.at<double>(1);
		pose1.z = bP.at<double>(2);
		pose1.rol = pose.rol;
		pose1.pit = pose.pit;
		pose1.yal = pose.yal;

		poses_b.push_back(pose1);

		// low level ctrl coord sys
		tmp_vect.clear();
		//pose1.x = -pose1.x;
		//pose1.y = -pose1.y;
		tmp_vect.push_back(pose1.x);
		tmp_vect.push_back(pose1.y);
		tmp_vect.push_back(pose1.z);
		tmp_vect.push_back(pose1.rol); 
		tmp_vect.push_back(pose1.pit); 
		tmp_vect.push_back(pose1.yal);

		ViaPoint_vect.push_back(tmp_vect);
	}

	/*double ViaPoint_ar[5][6] = {{150.00, -150.00, -180.00, 0.00, -1.5707, 0.00},
								{150.00, -150.00, -260.00, 0.00, -1.5707, 0.00},
								{150.00, -150.00, -180.00, 0.00, -1.5707, 0.00},
								{-200.00, -150.00, -180.00, 0.00, -1.5707, 0.00},
								{-200.00, -150.00, -260.00, 0.00, -1.5707, 0.00}};

	Mat ViaPoint = Mat(5, 6, CV_64F, ViaPoint_ar);*/

	// check output
	/*for (int i=0; i<ViaPoint_vect.size(); i++)
	{
		for (int j=0; j<ViaPoint_vect[i].size(); j++)
		{
			cout << ViaPoint_vect[i][j] << " ";
		}
		cout << endl;
	}*/

	//getchar();
	Mat ViaPoint = Vect2Mat<double>(ViaPoint_vect);  // !!!!!!!!!!!!!! -> DONE

	cout << "size of ViaPoint:" << endl;
	MatInfo(ViaPoint);
	MATmtxdisp(ViaPoint);
	cout << endl << endl; 
	//MATmtxdisp(ViaPoint.row(0));
	//MATmtxdisp(ViaPoint.row(1));
	//getchar();
	int via_cnt = 15;
	// ******************************* End of Via Point Matrix

	// ******************************* Start of Stereo Vars
	BumbleBee2 bb2;

	// stereo vars
	Mat frameRGB = Mat::zeros(5, 10, CV_8UC3);
	Mat frame3D;
	Mat rawframe, recframe, dispframe;
	// ***********

	// bkgnd sub vars
	char* bkgnd_img = "background.jpg";
	BackgroundSubtractorMOG bgsubtractor;
	Mat bgmask, bgimg, segimg;
	int bgflg = 0;       // to invoke segmentation
	//Mat tmp;
	float x,y,z;
	int stereo_flg = 0;
	// ******************************* End of Stereo Vars

	while (1)
	{
		// ############ LOOPING PROCESSING
		// ***** read wc using DirectShow && read BB2 frame
		cam.getFrame(frame);
		imshow("Current Frame", frame);

		if (!stereo_flg)
		{
			bb2.getframe16(recframe, frameRGB, frame3D);
			imshow("stereo RGB image",frameRGB);
			/*imshow("stereo raw image",rawframe);
			imshow("stereo rectified image",recframe);
			imshow("stereo disparity image",dispframe);*/
			imshow("stereo 8bit rectified image",recframe);
			//cout << frame3D.at<Vec3f>(120, 160)[2] << endl;
		}

		// ***** some timing processing
		//time(&toc);
		//printf("Time different is: %0.2f (sec)\n",difftime(toc, tic));  // this is in sec
		//tic = toc;
		toc_cv = clock();
		t_cv = toc_cv - tic_cv;
		//printf("Time different is: %0.2f (sec)\n",((float)t_cv/CLOCKS_PER_SEC));  // this is in sec
		tic_cv = toc_cv;

		// ***** stereo segmentation
		if (!stereo_flg)
		{
			if (bgflg)
			{
				recframe.copyTo(segimg);

				bgsubtractor(segimg, bgmask, 0);

				refineSegments(segimg, bgmask, tmp);

				cvtColor(segimg, segimg, CV_GRAY2BGR);

				/*cout << "segimg info = \n";
				MatInfo(segimg);
				cout << "tmp info = \n";
				MatInfo(tmp);*/

				multiply(segimg, tmp, segimg, 1);    // mask is applied to image here

				tmp.convertTo(tmp, CV_32FC3, 1, 0);
				MatBinarize(tmp);					 // make segmented frame a binary mask
				multiply(frame3D, tmp, frame3D, 1);  // mask is applied to 3D points
				get3DCOM(frame3D, x, y, z);
				// check getWrlCoord
				/*x = 0;
				y = 0;
				z = 100;*/
				// end of checking
				printf("COM: (%0.2f, %0.2f, %0.2f) -> ",x,y,z);
				getWrlCoord(x,y,z);
				// safety z
				// ** standing pattern
				x = x - 150;  // 150
				z = z + 100;  // 70
				//z = z + 80; 
				// ** lying pattern
				//x = x - 200;  // 150
				//z = z + 50;  // 70
				printf("COM(world): (%0.2f, %0.2f, %0.2f) \n",x,y,z);

				imshow("segment result", segimg);   // segimg -> CV_8UC3 image
				waitKey(1);

				//sprintf(tmp_c1,"%s/segment_%d.jpg",argv[1],i);
				//imwrite(tmp_c1, img_arr[i]);			
			}
		}

		// ############ KEYBOARD PROCESSING
		char c = waitKey(1);

		if ((c == 'd')||(demo))
		//if (c == 'd')
		{
			demo = 1;

			// ** Select grasp pose
			
				// ***** End Grasp Selection
			} else
			{
				
				// * Call Jacobian calculation
				try
				{
				
				}
				catch (exception& e)
				{
					cout << e.what() << endl;    // this helps to ignore runtime-error

				}
				

		// ****** START move to pre-defined poses
		if (c=='g')
		{
			//c = 'm';
			demo = 0;
			VScaller.cnt_acc = 0;

			if (via_cnt < ViaPoint.rows)
			{
				// ********** START assign target pose and let's go
				cout << "## Go to view: " << via_cnt << endl;

				ViaPoint.row(via_cnt).copyTo(DstPose);
				pit = DstPose.at<double>(4);
				yaw = DstPose.at<double>(5);

				int ret = DSrb.TrajPlanner(OrgPoseJnt, DstPose, traj);

				if (ret)
				{
					//MATmtxdisp(traj/CV_PI*180);
					DstPose.copyTo(OrgPoseJnt);

					//getchar();
				}
				else 
				{
					printf("there is no good solution!!\n");
					//getchar();
					//return 1;
				}

				via_cnt++;
				// ********** END assign target pose and let's go
			} else
			{
				via_cnt = 0;  // restart the loop
			}
		}
		// ****** END move to pre-defined poses
	
		// ****** START Move to initial Pose
		if (c=='0')
		{
			// ****** initial SETUP 
			tmp = Mat::zeros(1,6,CV_64F);

			// 0, -CV_PI/6, 2*CV_PI/3, 0, 0, 0
			tmp.at<double>(0) = 0;
			tmp.at<double>(1) = -CV_PI/6;
			tmp.at<double>(2) = 2*CV_PI/3;
			tmp.at<double>(3) = 0;
			tmp.at<double>(4) = 0;
			tmp.at<double>(5) = CV_PI;    // tmp here is 6x1 mat

			int ret = DSrb.JTrajPlanner(tmp);  // TrajPlanner works with row vector

			if (ret)
			{
				//MATmtxdisp(traj/CV_PI*180);
				//DstPose.copyTo(OrgPoseJnt);

				//getchar();
			}
			else 
			{
				printf("there is no good solution!!\n");
				//getchar();
				//return 1;
			}
		}
		// ****** END Move to initial Pose

		// ****** Start Stereo Control
		// Note: move target object out of background scene before training or get BB2 ERROR
		if (c=='t')
		{
			bgflg = 1;

			printf(" ############ Start training!! ############ \n");

			// ***output background image
			//imwrite(bkgnd_img, recframe);  // use pre-written bkgnd_img
			
			// ***read background image & train
			bgimg = imread(bkgnd_img, 1);
			//bgsubtractor.noiseSigma = 10;    // 2.4.0 noiseSigma becomes protected
			callTrainingBkGnd(bgimg, bgsubtractor, bgmask);
		}

		if (c=='r')  // press Enter
		{
			// feed COM to DENSO
		
		}
		// ****** END Stereo Control

		// ***** restart stereo_flg & object detection
		if (c=='s')  
		{
		
		}

		// ****** auto-run demo
		if (c=='a')
		{
		
		}
		// ****** 

		// ****** go to arbitrary pose
		if (c=='1')
		{
			via_cnt = 20;
		}

		// ****** go to arbitrary pose

		if (c==27) break;
		else
			if (c=='c')
			{
				//wind_flag = 0;
			} 
			else
				if (c=='o')
				{
					//wind_flag = 1;
				}
	}

	return 0;
}