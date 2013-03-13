
#include "TextWork.h"

using namespace std;

const unsigned int NAME_SZ = 255;
const unsigned int FULLNAME_SZ = 510;

int writeTextFile(char* filename, const std::vector<string> lines)
{
	 

	return 1;
}

int readTextFile(char* filename, std::vector<string>& lines)
{

	string fullname_str;
	cout << filename << " will be read" << endl;
	ifstream TextFile = ifstream(filename);
	char line[250];

	// next version: returning 0 if file cannot open
	while (!TextFile.eof())
	{
		TextFile.getline(line, 250);

		//fullname_str = string(fullname);

		lines.push_back(line);

		cout << line << endl;

		//getchar();

		//cout << mask_name_arr[mask_name_arr.size()].c_str() << endl;
	}


    return 1;

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