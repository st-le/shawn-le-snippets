#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__

//#include "opencv2/opencv.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/highgui/highgui.hpp"

//#include <stdio.h>
//#include <string.h>
//#include <ctype.h>
//#include <vector>
#include <iostream>
#include <fstream>




class Logger
{
private:
	std::ofstream TextFile;

public:


	//int Logger::in(void);

//	int Logger::out(void);

	Logger::Logger(char* filename);
	
	Logger::~Logger();
	
};



#endif