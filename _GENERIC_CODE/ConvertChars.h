#pragma once

#include <Windows.h>
#include <string>

std::string ConvertWstrToStr(std::wstring input)
{
	// Вычисляем необходимый размер буфера для строки типа string
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, input.c_str(), -1, NULL, 0, NULL, NULL);

	// Создаем буфер для строки типа string
	std::string str(size_needed, 0);

	// Конвертируем wstring в string
	WideCharToMultiByte(CP_UTF8, 0, input.c_str(), -1, &str[0], size_needed, NULL, NULL);

	// Убираем нулевой символ, добавленный функцией WideCharToMultiByte
	str.pop_back();

	return str;
}

const char* ConvertWcharToChar(const wchar_t* input)
{
	// Вычисляем необходимый размер буфера для строки типа string
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, input, -1, NULL, 0, NULL, NULL);

	// Создаем буфер для строки типа string
	std::string str(size_needed, 0);

	// Конвертируем wstring в string
	WideCharToMultiByte(CP_UTF8, 0, input, -1, &str[0], size_needed, NULL, NULL);

	// Убираем нулевой символ, добавленный функцией WideCharToMultiByte
	str.pop_back();

	return str.c_str();
}

const wchar_t* ConvertCharToWchar(const char* input)
{
	// Get the length of the UTF-16 string
	int utf16Length = MultiByteToWideChar(CP_UTF8, 0, input, -1, NULL, 0);
	if (utf16Length == 0)
	{
		return L"";
	}

	// Allocate buffer for UTF-16 string
	wchar_t* wcharstr = new wchar_t[utf16Length];

	// Convert UTF-8 to UTF-16
	if (MultiByteToWideChar(CP_UTF8, 0, input, -1, wcharstr, utf16Length) == 0)
	{
		return L"";
	}

	return wcharstr;
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