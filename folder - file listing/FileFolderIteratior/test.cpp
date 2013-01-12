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


			string name_str = "12341234.jpg";
		
			// split the name
			//split(fields, name_str, is_any_of(","));
			std::istringstream  ss("12341234.jpg");
			while(!ss.eof())
			{
				string x; 
				getline(ss, x, ',');
				cout << x << endl;
			}

			//std::cout<<  <<std::endl;

	
	return;
}