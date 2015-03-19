
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>

using namespace std;
using namespace boost;

const unsigned int NAME_SZ = 255;
const unsigned int FULLNAME_SZ = 510;

int main(int argc, char **argv)
{
	long int area_tol;
	float hw_pxl_tol, height_pxl, width_pxl;

	cout << "Input new height pxl: "; 
	cin >> height_pxl;

	cout << "Input new width pxl: "; 
	cin >> width_pxl;

	cout << "Input new area_tol: "; 
	cin >> area_tol;

	cout << "Input new size pxl tolerance: "; 
	cin >> hw_pxl_tol;

	// read all as char array - line by line read
	int MAX = FULLNAME_SZ;
	char line[FULLNAME_SZ];
	string line_str, line_str_mod;   // I can initialize here
	vector<string> rec;

	ifstream LogIn("LHVision.cpp");
	ofstream LogOu("LHVision.out.cpp");

	typedef vector< string > split_vector_type;
	while (!LogIn.eof())
	{	
		// read a line
		LogIn.getline(line, MAX);
		cout << line << endl;

		// sparse that line
		line_str = string(line);

		// find using string algor
		//line_str_mod = ireplace_first_copy(line_str,"linh","son");

		int flg = 0;

		line_str_mod = "";
		if (find_first(line_str, "hw_ref_pxl.height") == 1 && find_first(line_str, "*/") == 0)
		{
			flg = 1;

			// split the line
			split_vector_type sub_str;
			split( sub_str, line_str, is_any_of(" "), token_compress_on ); 
			cout << sub_str[2] << endl;
			getchar();

			// create new string
			sub_str[2] = boost::lexical_cast<string>(height_pxl);
			for (int i=0; i<sub_str.size()-1; i++)
			{
				line_str_mod= line_str_mod +sub_str[i] +" ";
			}
			line_str_mod= line_str_mod +sub_str[sub_str.size()] +";";

			// out to file
			LogOu << line_str_mod << endl;
		}

		if (find_first(line_str, "hw_ref_pxl.width") == 1 && find_first(line_str, "*/") == 0)
		{
			flg = 1;

			// split the line
			split_vector_type sub_str;
			split( sub_str, line_str, is_any_of(" "), token_compress_on ); 
			cout << sub_str[2] << endl;
			getchar();

			// create new string
			sub_str[2] = boost::lexical_cast<string>(width_pxl);
			for (int i=0; i<sub_str.size()-1; i++)
			{
				line_str_mod= line_str_mod +sub_str[i] +" ";
			}
			line_str_mod= line_str_mod +sub_str[sub_str.size()] +";";

			// out to file
			LogOu << line_str_mod << endl;
		}
	

		if (flg == 0)
		{
			LogOu << line_str << endl;
		}

		//cout << line_str << endl;
		//cout << line_str_mod << endl;
		//LogOu << line_str_mod << endl;
	}

}