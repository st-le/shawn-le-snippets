#include <iostream> 
#include <stdlib.h> 
#include <string> 

using namespace std; 
using namespace System; 

void char2wchar_t(char* charStr, wchar_t*& wcharStr)
{


	// Convert to a wchar_t* 
	size_t origsize = strlen(charStr) + 1; 
	const size_t newsize = 100; 
	size_t convertedChars = 0; 
	wchar_t wcstring[newsize]; 
	mbstowcs_s(&convertedChars, wcstring, origsize, charStr, _TRUNCATE); 
	wcscat_s(wcstring, L" (wchar_t *)"); 

}

int main() 
{ 
	// original char array
	char *orig = "I'm le trung son!"; 
	cout << orig << " (char *)" << endl; 

const size_t newsize = 100; 
	wchar_t* wcstring; //[newsize]; 
	
	char2wchar_t(orig, wcstring);
	/*
	// Convert to a wchar_t* 
	size_t origsize = strlen(orig) + 1; 
	const size_t newsize = 100; 
	size_t convertedChars = 0; 
	wchar_t wcstring[newsize]; 
	mbstowcs_s(&convertedChars, wcstring, origsize, orig, _TRUNCATE); 
	wcscat_s(wcstring, L" (wchar_t *)"); 
	*/
	
	// output result
	wcout << wcstring << endl; 
	getchar();
} 
