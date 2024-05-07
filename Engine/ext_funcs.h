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

const std::vector<std::wstring> wexplode(const std::wstring& s, const wchar_t& c)
{
	std::wstring buff{ L"" };
	std::vector<std::wstring> v;

	for (auto n : s)
	{
		if (n != c) buff += n; else
			if (n == c && buff != L"") { v.push_back(buff); buff = L""; }
	}
	if (buff != L"") v.push_back(buff);

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

std::wstring* SplitPosWStr(std::wstring wstr)
{
	std::wstring* arr = new std::wstring[3];

	std::vector<std::wstring> result = wexplode(wstr, L' ');

	for (size_t i = 0; i < result.size(); i++) {
		arr[i] = result[i];
	}

	return arr;
}