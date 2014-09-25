// v1.0 25/04/13: main program to deploy TextWork class
//				  read line by line, delimit numbers by ',', potentially used for DENSO read 6 position num [x,y,z,r,p,y]


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "TextWork.h"

using namespace std;

const unsigned int NAME_SZ = 255;
const unsigned int FULLNAME_SZ = 510;



int main(int argc, char** argv)
{
	// create a log file
	//ofstream logger(".\\LOG\\log1.txt");
	ofstream LoggerIn("log1.txt");

	// vars with different types
	float a = 3.14; 
	long int b = 123412343241234; 
	float c = 123.412343241234; 
	double d = 3.1415926535897932384626433832795;
	char e = 'f';
	char *f = "le trung son";
	string myname = "tu thi kim ha";

	// record the log
	/*LoggerIn << a << endl;
	LoggerIn << b << endl;
	LoggerIn << c << endl;
	LoggerIn << d << endl;
	LoggerIn << e << endl;
	LoggerIn << *f << endl;
	LoggerIn << myname << endl;*/
	LoggerIn << a << "," << 2*a << "," << 3*a << "," << 4*a << "," << 5*a << "," << 6*a << endl;
	LoggerIn << a << "," << 2*a << "," << 3*a << "," << 4*a << "," << 5*a << "," << 6*a << endl;
	LoggerIn << a << "," << 2*a << "," << 3*a << "," << 4*a << "," << 5*a << "," << 6*a << endl;
	LoggerIn << a << "," << 2*a << "," << 3*a << "," << 4*a << "," << 5*a << "," << 6*a << endl;
	LoggerIn << a << "," << 2*a << "," << 3*a << "," << 4*a << "," << 5*a << "," << 6*a << endl;
	LoggerIn << a << "," << 2*a << "," << 3*a << "," << 4*a << "," << 5*a << "," << 6*a << endl;

	// how about output type?
	ifstream LoggerOut("log1.txt");
	int A; 
	long int B;
	float C; 
	double D;
	char E;
	//while (!LoggerOut.eof())
	{
		//	LoggerOut >> A >> B >> C >> D >> E;     // read with known type -> wrong reading type
		//	cout << A << endl;
		//	cout << B << endl;
		//	cout << C << endl;
		//	cout << D << endl;
		//	cout << E << endl;
	}

	//cout << endl;

	// read all as char array - line by line read
	cout << "##### what I have read =" << endl;
	int MAX = 100;
	char line[100];
	vector<string> substr;

	float line_num[6];
	float total;

	while (!LoggerOut.eof())   // text input
	{	
		LoggerOut.getline(line, MAX);
		//LoggerOut.getline(line, MAX, Delimiter);  // Delimiter helps to sparse the line

		StrDelimit(line, ',', substr);

		//cout << substr.size() << endl;
		total = 0;
		for (int i = 0; i<substr.size()-1; i++)      // ATTENTION: this is size + 1!!!!
		{
			line_num[i] = atof(substr[i].c_str());
			total = total + line_num[i];

			cout << total << " ";
		}
		cout << endl;
//		cout << line << endl;
	}

	getchar();

	return 0;
}