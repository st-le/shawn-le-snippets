#include "FolderSparser.h"

using namespace std;
using namespace cv;


// input: mask_name_arr + training_img_name_arr
// output: mask_arr + training_img_arr
// iterate through the vector of names and read the real images
int getImageList(char dir[FULLNAME_SZ], const vector<string> name_arr, vector<Mat>& image_arr)
{
	Mat img;
	char fullname[FULLNAME_SZ];

	for (int i = 0; i<name_arr.size(); i++)
	{
		sprintf(fullname, "%s/%s",dir, name_arr[i].c_str());

		img = imread(fullname, 1);    // choose '1' to read background image, '0' to read mask image

		image_arr.push_back(img);
	}

	return 1;
}


int FolderSparser(char Directory[FULLNAME_SZ], char FileList[NAME_SZ],
		 std::vector<cv::Mat>& received_img)
{

	// get db image list
	char tmpfullstr[FULLNAME_SZ];
	char tmpfullstr1[FULLNAME_SZ];

	vector<string> img_name_list;
	sprintf(tmpfullstr, "%s/%s", Directory, FileList);
	//sprintf(tmpfullstr1, "%s/%s", Testdir, Testfilelist);
	readTextFile(tmpfullstr, img_name_list);

	// *** read image
	//vector<Mat> db_img;
	getImageList(Directory, img_name_list, received_img);

	return 1;
}