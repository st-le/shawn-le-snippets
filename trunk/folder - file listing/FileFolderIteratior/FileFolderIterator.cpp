// 06/01/13: run OK -> change Unicode character set to Multi-Byte character set
// 02/02/13: add return vector<string> to function

#include <string.h>
#include <iostream>
#include <windows.h> 
#include <vector>

using namespace std;

void ListDirRec(const char *s); 

void ListDirRec(const char *s, vector<string> DirFileList);

int main(){    

	std::cout<<"Contents of c:\n";    
	//ListDirRec("C:/");    

	vector<string> DirFileList;
	//ListDirRec("D:/WORK/WORK/NTUST/projects/Visual Studio 2008/Projects/WriteWC2Frames-use this one/WriteWC2Frames/Debug/greencart_3/", DirFileList);
	ListDirRec("D:/WORK/WORK/NTUST/projects/hybrid visual servoing/DATABASE/Two_objects_Jan_24_Renamed/", DirFileList);

	getchar();
	return 0;
} 

void ListDirRec(const char *s){    

	char sDir[MAX_PATH]="\0", sTmp[MAX_PATH]="\0";    
//	wchar_t sDir[MAX_PATH]="\0", sTmp[MAX_PATH]="\0";    

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
			strcat(sTmp, "\\");            			
			ListDirRec(sTmp);        
		}else
		{            
			std::cout<<s<<theFiles.cFileName<<std::endl;        
		}    
	} while(FindNextFile(hTheFiles, &theFiles));     

	FindClose(hTheFiles);
	
	return;
}

void ListDirRec(const char *s, vector<string> DirFileList)
{    

	char sDir[MAX_PATH]="\0", sTmp[MAX_PATH]="\0";    
	//	wchar_t sDir[MAX_PATH]="\0", sTmp[MAX_PATH]="\0";    
	char tmp[MAX_PATH];
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
			//strcat(sTmp, "\\");            			
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
				cout << "An exception occurred. Exception Nr." << e << endl;
			}
		}    
	} while(FindNextFile(hTheFiles, &theFiles));     

	FindClose(hTheFiles);

	return;
}