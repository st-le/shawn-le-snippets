// v1.0 24/02/13: successfully delimit a string by a given delimiter
// v2.0 24/02/13: modularized & used to recognize filetype -> continue this later!!!!!

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

const unsigned int NAME_SZ = 255;
const unsigned int FULLNAME_SZ = 510;

void StrDelimit(string str, char del, vector<string>& substr)
{

	//stringstream ss(line_str);  // stringstream can work
	istringstream ss(str);   // istringstream still works fine

	char rec_sub[NAME_SZ];

	while (ss)
	{
		//string rec_sub;

		//getline(ss, rec_sub, del);
		ss.getline(rec_sub, NAME_SZ, del);
		substr.push_back(rec_sub);
		//LoggerOut.getline(line, MAX, Delimiter);  // Delimiter helps to sparse the line

//		cout << rec_sub << endl;
//		getchar();
	}
}

void GetFileExtension(string filename, char* extension)
{
	vector<string> rec;

	StrDelimit(filename, '.', rec);

	//cout << rec[rec.size()-2].c_str()[1] << endl;
	
	//extension = rec[rec.size()-2].c_str()[0];

	//extension = &rec[rec.size()-2].c_str()[0];

	string str = rec[rec.size()-2];

	// conversion from string to char*
	vector<char> writable(str.size() + 1);

	std::copy(str.begin(), str.end(), writable.begin());

	//cout << writable << endl;

	extension = &writable[0];
}

void GetFileExtension(string filename, string& extension)
{
	vector<string> rec;

	StrDelimit(filename, '.', rec);

	//cout << rec[rec.size()-2].c_str()[1] << endl;

	//extension = rec[rec.size()-2].c_str()[0];

	//extension = &rec[rec.size()-2].c_str()[0];

	extension = rec[rec.size()-2];	
}


int main(int argc, char** argv)
{
	// how about output type?
	ifstream LoggerOut("log1.txt");
	
	// read all as char array - line by line read
	int MAX = FULLNAME_SZ;
	char line[FULLNAME_SZ];
	string line_str;   // I can initialize here
	vector<string> rec;

	StrDelimit("d/folder/fodler12/file.jpg", '/', rec);

	cout << rec.size() << endl;

	cout << rec[rec.size()-2] << endl;   // -2 to get the last element after delimiting

	//char ext[NAME_SZ];
	//GetFileExtension(rec[rec.size()-2], &ext[0]);
	//cout << ext << endl;

	string ext;
	GetFileExtension(rec[rec.size()-2], ext);
	cout << ext << endl;

	getchar();

//	while (!LoggerOut.eof())
//	{	
//		// read a line
//		LoggerOut.getline(line, MAX);
//		cout << line << endl;
//		getchar();
//
//		// sparse that line
////		string line_str(line);     // or initialize here
//		line_str = string(line);
//
//		//stringstream ss(line_str);  // stringstream can work
//		istringstream ss(line_str);   // istringstream still works fine
//
//		while (ss)
//		{
//			string rec_sub;
//			getline(ss, rec_sub, '/');
//			rec.push_back(rec_sub);
//			//LoggerOut.getline(line, MAX, Delimiter);  // Delimiter helps to sparse the line
//
//			 cout << rec_sub << endl;
//			 getchar();
//		}
//	}

	return 0;
}