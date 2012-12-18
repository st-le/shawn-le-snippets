// constructing maps
#include <iostream>
#include <map>

using namespace std;

int main(void)
{
	map<char,int> first;

	first['z'] = 2;
	first['y'] = 15;
	first['a'] = 1;
	first['c'] = 5;
	first['m'] = 6;

	map<char,int>::iterator it;

	it = first.begin();

	it++;
	it++;
	it++;

	printf("first element is:: ");

	cout << it->first << " -> " << it->second << endl;

	getchar();

	return 0;
}