#include "Logger.hpp"

//using namespace cv; 
using namespace std;


/*
int Logger::in(void)
{

	return 1;
}

int Logger::out(void)
{

	return 1;
}
*/

Logger::Logger(char* filename)
{
	TextFile = ofstream(filename);
}

Logger::~Logger()
{

}