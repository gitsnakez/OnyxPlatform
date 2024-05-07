#pragma once

#include <string>
#include <Windows.h>

std::string ConvertWstrToStr(const wchar_t* input)
{
	// ��������� ����������� ������ ������ ��� ������ ���� string
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, input, -1, NULL, 0, NULL, NULL);

	// ������� ����� ��� ������ ���� string
	std::string str(size_needed, 0);

	// ������������ wstring � string
	WideCharToMultiByte(CP_UTF8, 0, input, -1, &str[0], size_needed, NULL, NULL);

	// ������� ������� ������, ����������� �������� WideCharToMultiByte
	str.pop_back();

	return str;
}

std::wstring ConvertStrToWstr(std::string input)
{
	// Get the length of the UTF-16 string
	int utf16Length = MultiByteToWideChar(CP_UTF8, 0, input.c_str(), -1, NULL, 0);
	if (utf16Length == 0)
	{
		return L"";
	}

	// Allocate buffer for UTF-16 string
	wchar_t* wcharstr = new wchar_t[utf16Length];

	// Convert UTF-8 to UTF-16
	if (MultiByteToWideChar(CP_UTF8, 0, input.c_str(), -1, wcharstr, utf16Length) == 0)
	{
		return L"";
	}

	return wcharstr;
}