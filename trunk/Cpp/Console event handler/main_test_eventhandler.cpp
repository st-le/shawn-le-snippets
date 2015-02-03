
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <iostream>

#include "ConsolWinHandler.h"

using namespace std;

int escape;

int main() {

	int ret = 0;

	escape = 0;

	setWinCloseHandler();

	char c;
	while (1)
	{

		cin >> c;
		if (c == 'c'  || escape == 1) 
		{
			break;
		}
	}
	
	printf("Program ends at main thread!\n");
	getchar();
	return ret;

}