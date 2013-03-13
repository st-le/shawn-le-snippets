#include "FolderSparser.h"

using namespace std;
using namespace cv;
using namespace boost::filesystem;


// input: mask_name_arr + training_img_name_arr
// output: mask_arr + training_img_arr
// iterate through the vector of names and read the real images
//int getImagefrmNmLst(char dir[FULLNAME_SZ], const vector<string> name_arr, vector<Mat>& image_arr)
//int getImagefrmNmLst(const char* dir, const vector<string> name_arr, vector<Mat>& image_arr)
int getImagefrmNmLst(const vector<string> name_arr, vector<Mat>& image_arr)
{
	Mat img;
	//char fullname[FULLNAME_SZ];

	for (int i = 0; i<name_arr.size(); i++)
	{
		//sprintf(fullname, "%s/%s",dir, name_arr[i].c_str());

		img = imread(name_arr[i], 1);    // choose '1' to read background image, '0' to read mask image

		image_arr.push_back(img);
	}

	return 1;
}
//
//int getImageList(const vector<string> name_arr, vector<Mat>& image_arr)
//{
//	Mat img;
//	char fullname[FULLNAME_SZ];
//
//	for (int i = 0; i<name_arr.size(); i++)
//	{
//		//sprintf(fullname, "%s/%s",dir, name_arr[i].c_str());
//		cout << name_arr[i] << endl;
//
//		img = imread(name_arr[i], 1);    // choose '1' to read background image, '0' to read mask image
//
//		image_arr.push_back(img);
//	}
//
//	return 1;
//}

//int FolderSparser(char Directory[FULLNAME_SZ], char FileList[NAME_SZ],
//		 std::vector<cv::Mat>& received_img)
//{
//
//	// get db image list
//	char tmpfullstr[FULLNAME_SZ];
//	char tmpfullstr1[FULLNAME_SZ];
//
//	vector<string> img_name_list;
//	sprintf(tmpfullstr, "%s/%s", Directory, FileList);
//	//sprintf(tmpfullstr1, "%s/%s", Testdir, Testfilelist);
//	readTextFile(tmpfullstr, img_name_list);
//
//	// *** read image
//	//vector<Mat> db_img;
//	getImageList(Directory, img_name_list, received_img);
//
//	return 1;
//}
//
//int FolderSparser(char Directory[FULLNAME_SZ],
//				  std::vector<cv::Mat>& received_img)
//{
//
//	// get db image list
//	char tmpfullstr[FULLNAME_SZ];
//	char tmpfullstr1[FULLNAME_SZ];
//
//	vector<string> img_name_list;
//	//sprintf(tmpfullstr, "%s/%s", Directory, FileList);
//	//sprintf(tmpfullstr1, "%s/%s", Testdir, Testfilelist);
//	//readTextFile(tmpfullstr, img_name_list);
//	ListDirRec(Directory, img_name_list);
//	cout << img_name_list.size() << endl;
////	getchar();
//
//	// remove non-image file
//	vector<string> rec;
//	for (int i=0; i<img_name_list.size();  i++)
//	{
//		StrDelimit(img_name_list[i], '/', rec);
//
//		string ext;
//		GetFileExtension(rec[rec.size()-2], ext);
//
//		//cout << ext << endl;
//
//		if (ext.compare(string("jpg")) != 0)
//		{
//			cout << img_name_list[i] << " is not an image" << endl;
//
//			//getchar();
//
//			//img_name_list.erase(img_name_list.begin() + );
//		}
//	}
//
//
//	// *** read image
//	vector<Mat> db_img;
//	getImageList(img_name_list, received_img);
//	//getImageList(Directory, img_name_list, received_img);
//
//	return 1;
//}

int GetImageinDir(const char* Dir,
				  std::vector<cv::Mat>& received_img)
{
		// get db image list
		vector<string> img_name_list;

		ListDirRec(Dir, img_name_list, ".jpg");

		cout << img_name_list.size() << endl;

		// *** read image
		Mat img;
		
		for (int i = 0; i<img_name_list.size(); i++)
		{
			//sprintf(fullname, "%s/%s",dir, name_arr[i].c_str());

			img = imread(img_name_list[i], 1);    // choose '1' to read background image, '0' to read mask image

			received_img.push_back(img);
		}

		return 1;
}


void ListDirRec(const char *Dir, vector<string>& DirFileList, const char* ext)
{    

	recursive_directory_iterator rdi(Dir);  
	recursive_directory_iterator end_rdi;

	DirFileList.empty();

	string ext_str0(ext);	
	for (; rdi != end_rdi; rdi++)
	{
		rdi++;
		//cout << (*di).path().string() << endl;
		cout << (*rdi).path().string() << endl;
	
		//cout << " <----- " << (*rdi).path().extension() << endl;
		
		//string ext_str1 = (*rdi).path().extension().string();
		if (ext_str0.compare((*rdi).path().extension().string()) == 0)
		{
			DirFileList.push_back((*rdi).path().string());
		}
	}

	//getchar();

	/*
	path p (s);   // p reads clearer than argv[1] in the following code

  try
  {
    if (exists(p))    // does p actually exist?
    {
      if (is_regular_file(p))        // is p a regular file?   
        cout << p << " size is " << file_size(p) << '\n';

      else if (is_directory(p))      // is p a directory?
      {
        cout << p << " is a directory containing:\n";

        copy(directory_iterator(p), directory_iterator(), // directory_iterator::value_type
          ostream_iterator<directory_entry>(cout, "\n")); // is directory_entry, which is
                                                          // converted to a path by the
                                                          // path stream inserter
      }

      else
        cout << p << " exists, but is neither a regular file nor a directory\n";
    }
    else
      cout << p << " does not exist\n";
  }

  catch (const filesystem_error& ex)
  {
    cout << ex.what() << '\n';
  }
  */


  //getchar();
}

/*
void ListDirRec(const char *s, vector<string>& DirFileList)
{    

	char sDir[FULLNAME_SZ]="\0", sTmp[FULLNAME_SZ]="\0";    
	//	wchar_t sDir[FULLNAME_SZ]="\0", sTmp[FULLNAME_SZ]="\0";    
	char tmp[FULLNAME_SZ];
	string tmp_str;

	WIN32_FIND_DATA theFiles;    

	HANDLE hTheFiles;     

	ZeroMemory(&theFiles, sizeof(WIN32_FIND_DATA));   

	strcpy(sDir, s);    
	strcat(sDir, "*");     
	hTheFiles = FindFirstFile(sDir, &theFiles);    

	if(hTheFiles==INVALID_HANDLE_VALUE) return;     
	sDir[strlen(sDir)-1]=0;     

	do{        
		if( (!strcmp(".", theFiles.cFileName)) || (!strcmp("..", theFiles.cFileName)) )            
			continue;         

		if(theFiles.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			strcpy(sTmp, sDir);            
			strcat(sTmp, theFiles.cFileName);            
			strcat(sTmp, "/");            			
			ListDirRec(sTmp, DirFileList);        
		}else
		{            
			std::cout<<s<<theFiles.cFileName<<std::endl;
			try 
			{
				sprintf(tmp,"%s%s",s, theFiles.cFileName);
				tmp_str = tmp;
				DirFileList.push_back(tmp_str);
			}
			catch (int e)
			{
				cout << "An exception occurred. Exception No." << e << endl;
			}
		}    
	} while(FindNextFile(hTheFiles, &theFiles));     

	FindClose(hTheFiles);

	return;
}
*/