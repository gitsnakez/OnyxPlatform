#pragma once

#include <string>
#include <vector>

const std::vector<std::string> explode(const std::string& s, const char& c)
{
	std::string buff{ "" };
	std::vector<std::string> v;

	for (auto n : s)
	{
		if (n != c) buff += n; else
			if (n == c && buff != "") { v.push_back(buff); buff = ""; }
	}
	if (buff != "") v.push_back(buff);

	return v;
}

std::string* SplitPosStr(std::string str)
{
	std::string* arr = new std::string[3];

	std::vector<std::string> result = explode(str, ' ');

	for (size_t i = 0; i < result.size(); i++) {
		arr[i] = result[i];
	}

	return arr;
}