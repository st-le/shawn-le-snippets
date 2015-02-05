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


int main(int argc, char** argv)
{

	int MAX = FULLNAME_SZ;
	char line[FULLNAME_SZ];
	string line_str, line_out;   // I can initialize here
	vector<string> rec;
	
	ifstream LoggerIn("abc.txt");
	ofstream LoggerOut("abc_out.txt");
	while (!LoggerIn.eof())
	{	
		// read a line
		LoggerIn.getline(line, MAX);
		cout << line << endl;
		//getchar();

		// sparse that line
		line_str = string(line);

		istringstream ss(line_str);   // istringstream still works fine

		line_out = "";
		string rec_sub;
		while (ss)
		{
			getline(ss, rec_sub, ' ');

			if (rec_sub.compare("linh") == 0 || rec_sub.compare("Linh") == 0) 
			{
				rec.push_back("son");
				line_out = line_out +" son";
			} else
			{
				rec.push_back(rec_sub);
				line_out = line_out +rec_sub +" ";
			}
		}
		cout << line_out << endl;
		LoggerOut << line_out << endl;
		getchar();

	}

	return 0;
}