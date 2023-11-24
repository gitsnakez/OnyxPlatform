#include "file_reader.h"

file_reader::file_reader()
{
}

file_reader::~file_reader()
{
}

std::map<std::string, std::string> file_reader::GetHeaderDictionaryFromFile(const wchar_t* filename)
{
    std::ifstream file;
    file.open(filename);

    if (!file.is_open())
        throw new std::exception("file_reader: Filestream wasn't open!");

    // Info block
    std::map<std::string, std::string> result;
    std::string line;

    // Regular expression block
    std::cmatch matches;
    std::regex regular = std::regex("^(.*?)\\s*:\\s*(.*?)$");

    while (!file.eof())
    {
        getline(file, line);

        if (std::regex_match(line.c_str(), matches, regular))
        {
            result[matches[1]] = matches[2];
        }
    }

    file.close();

    return result;
}