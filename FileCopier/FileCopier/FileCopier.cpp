// created (04/09/12): from SO Q&A -> fail to work

#include <fstream> 
#include <iostream> 
#include <ctime> 

using namespace std; 

int main() 
{ 
	clock_t start, end; 
	start = clock(); 

	ifstream source("D:\asdf.txt", ios::binary); 
	ofstream dest("D:\asdf_copy.txt", ios::binary); 

	// file size 
	source.seekg(0, ios::end); 
	ifstream::pos_type size = source.tellg(); 
	source.seekg(0); 
	// allocate memory for buffer 
	char* buffer = new char[size]; 

	// copy file     
	source.read(buffer, size); 
	dest.write(buffer, size); 

	// clean up 
	delete[] buffer; 
	source.close(); 
	dest.close(); 

	end = clock(); 

	cout << "CLOCKS_PER_SEC " << CLOCKS_PER_SEC << "\n"; 
	cout << "CPU-TIME START " << start << "\n"; 
	cout << "CPU-TIME END " << end << "\n"; 
	cout << "CPU-TIME END - START " <<  end - start << "\n"; 
	cout << "TIME(SEC) " << static_cast<double>(end - start) / CLOCKS_PER_SEC << "\n"; 

	return 0; 
} 
