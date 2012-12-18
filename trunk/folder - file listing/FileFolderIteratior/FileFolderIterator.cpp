#include <string.h>
#include <iostream>
#include <windows.h> 

void ListDirRec(const char *s); 

int main(){    

	std::cout<<"Contents of c:\n";    
	ListDirRec("c:\\");    
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