// v1.0 (04/09/12): from SO Q&A -> fail to work

#include <fstream> 
#include <iostream> 
#include <ctime> 

using namespace std; 

int main() 
{ 
	clock_t start, end; 
	start = clock(); 

	ifstream source("D:\asdf.txt"); 
	ofstream dest("D:\asdf_copy.txt"); 

	dest << source.rdbuf();

	end = clock(); 

	cout << "CLOCKS_PER_SEC " << CLOCKS_PER_SEC << "\n"; 
	cout << "CPU-TIME START " << start << "\n"; 
	cout << "CPU-TIME END " << end << "\n"; 
	cout << "CPU-TIME END - START " <<  end - start << "\n"; 
	cout << "TIME(SEC) " << static_cast<double>(end - start) / CLOCKS_PER_SEC << "\n"; 

	getchar();

	return 0; 
} 
