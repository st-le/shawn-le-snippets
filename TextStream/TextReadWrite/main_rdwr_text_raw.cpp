

#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int main(int argc, char** argv)
{

	// create a log file
	//ofstream logger(".\\LOG\\log1.txt");
	ofstream LoggerIn("log1.txt");

	// vars with different types
	int a = 12; 
	long int b = 123412343241234; 
	float c = 123.412343241234; 
	double d = 3.1415926535897932384626433832795;
	char e = 'f';
	char *f = "le trung son";
	string myname = "tu thi kim ha";

	// record the log
	LoggerIn << a << endl;
	LoggerIn << b << endl;
	LoggerIn << c << endl;
	LoggerIn << d << endl;
	LoggerIn << e << endl;
	LoggerIn << *f << endl;
	LoggerIn << myname << endl;

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
	int MAX = 100;
	char line[100];
	while (!LoggerOut.eof())
	{	
		LoggerOut.getline(line, MAX);
		//LoggerOut.getline(line, MAX, Delimiter);  // Delimiter helps to sparse the line
		cout << line << endl;
	}

	
	getchar();

	return 0;
}