#ifndef __TEXTWORK_H__
#define __TEXTWORK_H__

#include <stdio.h>
#include <cstdio>
#include <iostream>
#include <fstream>

#include <string>
#include <vector>

int writeTextFile(char* filename, const std::vector<std::string> lines);

int readTextFile(char* filename, std::vector<std::string>& lines);


#endif // TEXTWORK_H
