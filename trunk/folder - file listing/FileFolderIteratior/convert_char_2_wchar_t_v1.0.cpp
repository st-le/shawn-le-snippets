#include <iostream> 
#include <stdlib.h> 
#include <string> 
 
using namespace std; 
using namespace System; 
 
int main() 
{ 
    char *orig = "Hello, World!"; 
    cout << orig << " (char *)" << endl; 
 
    // Convert to a wchar_t* 
    size_t origsize = strlen(orig) + 1; 
    //const size_t newsize = 100; 
    size_t convertedChars = 0; 
    //wchar_t wcstring[newsize]; 
	wchar_t wcstring[newsize]; 
    mbstowcs_s(&convertedChars, wcstring, origsize, orig, _TRUNCATE); 
    wcscat_s(wcstring, L" (wchar_t *)"); 
    wcout << wcstring << endl; 

	getchar();
} 
