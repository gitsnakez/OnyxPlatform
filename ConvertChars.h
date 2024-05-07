#pragma once

#include <string>

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