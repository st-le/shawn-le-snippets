


#include <stdio.h>
#include <string>

#include <cstdio>
#include <iostream>
#include <fstream>



void string_processor(char *pt_str)	
{

	// assignment like following cannot be used for char array or char poitner
	//pt_str = "letrungson";
	//pt_str = "letr";
	
	// MUST use strcat
	//strcat(pt_str, "letrung");

	// int n = 3;  // with case (1), n is low/small
	int n = 70;    // with case (2), n can be as large as the allocated memory size

	for (int i=0;i<n;i++)
		strcat(pt_str, "c");
}


int main(int argc, char** argv)
{
	
	char *pt;

	// (1) without memory allocation
	//char ch_ar[]="";

	// (2) with memory allocation => BETTER
	char ch_ar[100]="";

	pt = ch_ar;

	//string_processor(pt);
	string_processor(ch_ar);

	// INTERESTING!! strcat cannot add string longer than 7 character. the 8th one will create error. It MUST be pre-allocated with memory before assigning big string
	//strcat(pt, "letrungson");
	//strcat(pt, "letrungo");

	//strcat(pt, "letrung");

	printf("String poitner = %s\n\n",pt);
	printf("String var = %s",ch_ar);
	getchar();

	//delete ch_ar;
	//delete pt;

	// using pointer creates error at program's end
	
	return 1;

}