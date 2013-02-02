
#include "TextWork.h"

using namespace std;

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
