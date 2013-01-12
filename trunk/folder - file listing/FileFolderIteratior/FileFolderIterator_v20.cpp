// 06/01/13: run OK -> change Unicode character set to Multi-Byte character set
// 06/01/13: use to split file name for image database

#include <string.h>
#include <iostream>
#include <windows.h> 

#include <vector>

//#include <boost/regex.hpp>
//#include <boost/algorithm/string/regex.hpp>

using namespace std;
//using namespace boost;

void ListDirRec(const char *s); 

int main(){    

	std::cout<<"Contents of c:\n";    
	ListDirRec("Y:/Zola/Training Image/output/masks/");    
	return 0;
} 

void ListDirRec(const char *s){    

	char sDir[MAX_PATH]="\0", sTmp[MAX_PATH]="\0";    
//	wchar_t sDir[MAX_PATH]="\0", sTmp[MAX_PATH]="\0"; 

	char name[MAX_PATH]="";
	//string name_str;
	vector<string> fields;

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
			// get the name
			//name = theFiles.cFileName;
			//name_str = name;
			//string name_str(theFiles.cFileName);
			string name_str = "12341234.jpg";
		
			// split the name
			//split(fields, name_str, is_any_of(","));
			istringstream  ss(name_str);
			while(!ss.eof())
			{
				string x; 
				getline(ss, x, ',');
				cout << x << endl;
			}

			std::cout<<theFiles.cFileName<<std::endl;
			//std::cout<<s<<theFiles.cFileName<<std::endl;
		}    
	} while(FindNextFile(hTheFiles, &theFiles));     

	FindClose(hTheFiles);
	
	return;
}