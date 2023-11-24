#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "ExceptHelper.h"
#include <map>
#include <regex>

class file_reader
{
public:
	file_reader();
	~file_reader();

	std::map<std::string, std::string> GetHeaderDictionaryFromFile(const wchar_t* filename);
};