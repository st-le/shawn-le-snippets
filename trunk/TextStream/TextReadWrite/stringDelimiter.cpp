// 24/02/13: successfully delimit a string by a given delimiter

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int main(int argc, char** argv)
{
	// how about output type?
	ifstream LoggerOut("log1.txt");
	
	// read all as char array - line by line read
	int MAX = 100;
	char line[100];
	string line_str;   // I can initialize here
	vector<string> rec;

	while (!LoggerOut.eof())
	{	
		// read a line
		LoggerOut.getline(line, MAX);
		cout << line << endl;
		getchar();

		// sparse that line
//		string line_str(line);     // or initialize here
		line_str = string(line);

		//stringstream ss(line_str);  // stringstream can work
		istringstream ss(line_str);   // istringstream still works fine

		while (ss)
		{
			string rec_sub;
			getline(ss, rec_sub, '/');
			rec.push_back(rec_sub);
			//LoggerOut.getline(line, MAX, Delimiter);  // Delimiter helps to sparse the line

			 cout << rec_sub << endl;
			 getchar();
		}
	}

	return 0;
}