#pragma once

#include <string>

std::string ConvertWstrToStr(const wchar_t* input)
{
	// Вычисляем необходимый размер буфера для строки типа string
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, input, -1, NULL, 0, NULL, NULL);

	// Создаем буфер для строки типа string
	std::string str(size_needed, 0);

	// Конвертируем wstring в string
	WideCharToMultiByte(CP_UTF8, 0, input, -1, &str[0], size_needed, NULL, NULL);

	// Убираем нулевой символ, добавленный функцией WideCharToMultiByte
	str.pop_back();

	return str;
}