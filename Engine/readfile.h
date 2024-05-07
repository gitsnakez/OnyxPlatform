#pragma once

#include <Windows.h>
#include <filesystem>
#include <fstream>
#include <vector>
#include <string>
#include <locale>
#include <regex>
#include <iostream>

#include "OnyxFileElement.h"


OnyxFileElement
	ReadFile(LPCWSTR filename);

void
	_getName(LPCWSTR filename, OnyxFileElement* element);

std::vector<std::wstring>
	_loadFile(LPCWSTR filename);

void
	_parseFile(std::vector<std::wstring> filelines, OnyxFileElement* ofe);

OnyxFileNode
	_parseNode(std::vector<std::wstring>& filelines, size_t& index);