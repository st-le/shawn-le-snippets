#ifndef __TEXTWORK_H__
#define __TEXTWORK_H__

#include <stdio.h>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <vector>

int writeTextFile(char* filename, const std::vector<std::string> lines);

int readTextFile(char* filename, std::vector<std::string>& lines);

void StrDelimit(std::string str, char del, std::vector<std::string>& substr);

void GetFileExtension(std::string filename, std::string& extension);

#endif // TEXTWORK_H