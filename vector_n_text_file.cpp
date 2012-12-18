
// basic file operations
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int vector_iteration(vector<string>& lines);

int readTextFile(vector<string>& lines)
{
 string line;
  ifstream myfile ("notes.txt");
  if (myfile.is_open())
  {
    while ( myfile.good() )
    {
      getline (myfile,line);
	  lines.push_back(line);   // append to vector
//      cout << line << endl;
    }
    myfile.close();
  }

  else cout << "Unable to open file"; 

  getchar();
  return 0;
}

int writeTextFile()
{
  ofstream myfile;
  myfile.open ("example.txt");
  myfile << "I'm Le Trung Son\n";
  myfile << "This is the writing to file test\n";
  myfile << "Writing this to a file.\n";
  myfile.close();
  return 0;
}

int vector_pop_push(vector<string>& lines)
{
	string line = "le trung son";

	printf("size of lines is = %d\n",lines.size());

	//printf("last line is:::%s\n",lines.back());
	//cout << line;
	printf("last line is:::");
	cout << lines.back() << endl;
	lines.pop_back();

	//printf("2nd last line is:::%s\n",lines.back());	
	printf("2nd last line is:::");	
	cout << lines.back() << endl;
	lines.pop_back();

	vector_iteration(lines);

	//getchar();

	return 0;
}

int vector_iteration(vector<string>& lines)
{
	vector<string>::iterator it;

	for(it = lines.begin(); it < lines.end(); it++)
	{
		cout << *it << endl;
	}

	getchar();

	return 0;
}

int vector_riteration(vector<string>& lines)
{
	vector<string>::reverse_iterator rit;

	for(rit = lines.rbegin(); rit < lines.rend(); rit++)
	{
		cout << *rit << endl;
	}

	getchar();

	return 0;
}

int vector_insert(vector<string>& lines)
{

	vector<string>::iterator it;

	vector<string> insertion;
	insertion.push_back("inserted line 0");
	insertion.push_back("inserted line 1");
	insertion.push_back("inserted line 2");
	
	it = lines.begin();

	lines.insert(it + 3, "inserted line 0");

	it = lines.end();

	lines.insert(it,insertion.begin(),insertion.end());
	
	vector_riteration(lines);

	getchar();

	return 0;
}

int use_vector(vector<string>& lines)
{
	//vector_pop_push(lines);

	//vector_iteration(lines);

	vector_insert(lines);
	
	return 0;
}

void  vector2D_iteration(vector< vector<int> >& mtx) // <- ref pass a 2D vector 
{
	vector<vector<int>>::iterator it2d;
	vector<int>::iterator it;
	vector<int> row;

	cout << mtx[2][5] << endl;

	int cnt = 0;

	for(int i = 0; i < mtx.size(); i++)
	{
		for(int j = 0; j < mtx[i].size() - cnt; j++)   // changed
		{
			cout << mtx[i][j+cnt] << " ";       // changed compared to matrix
		}

		cnt = cnt + mtx.size();

		cout << endl;		
	}


	getchar();

}


int test_2D_vector()
{
	vector<vector<int>> mtx;
	vector<int> row;

	row.push_back(1);
	row.push_back(2);
	row.push_back(3);
	mtx.push_back(row);

	row.push_back(4);
	row.push_back(5);
	row.push_back(6);
	mtx.push_back(row);

	row.push_back(7);
	row.push_back(8);
	row.push_back(9);
	mtx.push_back(row);

	// 2D vector cannot be created as a matrix 
/*	row.push_back(0);
	mtx.push_back(row);

	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			mtx[i][j] = i*3 + j;
		}
	}  */


//	cout << mtx[1][2] << endl; // <- element access is OK 

	getchar();
	vector2D_iteration(mtx);

	return 1;
}

int main () 
{
//	vector<string> lines;

	test_2D_vector();

//	readTextFile(lines);
//	use_vector(lines);

	return 0;
}
