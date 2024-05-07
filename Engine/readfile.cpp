#include "readfile.h"
#include "ErrorDispatcher.h"

#define REGEX_GROUP_LINE        L"[ \t]*([A-ZА-Яa-zа-я0-9_.]{2,64})[ \t]*"
#define REGEX_FORWARD_CARRET    L"[ \t]*[{]{1,1}.*?"
#define REGEX_BACKWARD_CARRET   L"[ \t]*[}]{1,1}.*?"
#define REGEX_CARRET_LINE       L"[ \t]*([A-ZА-Яa-zа-я0-9_.]{2,64})[ \t]*:[ \t]*\"([A-ZА-Яa-zа-я0-9.\_\\/]{0,64})\".*?"
#define REGEX_VECTOR3_LINE      L"[ \t]*([A-ZА-Яa-zа-я0-9_.]{2,64})[ \t]*:[ \t]*([-+]?[0-9]{0,12}[.?,?0-9]{1,5}[ \t]*[-+]?[0-9]{0,12}[.?,?0-9]{1,5}[ \t]*[-+]?[0-9]{0,12}[.?,?0-9]{1,5}).*?"


wregex rgxGroupLine         = wregex(REGEX_GROUP_LINE); // line with groupname and with no ":"
wregex rgxCarretLine        = wregex(REGEX_CARRET_LINE); // line with carets(quotes)
wregex rgxVec3Line          = wregex(REGEX_VECTOR3_LINE); // line with 3 floats
wregex rgxForwardCaret      = wregex(REGEX_FORWARD_CARRET); // line with { caret
wregex rgxBackwardCaret     = wregex(REGEX_BACKWARD_CARRET); // line with } caret


using namespace std;

OnyxFileElement ReadFile(LPCWSTR filename)
{
    if (filename[0] == (WCHAR)L"☐")
        ShowErrorMessage("Problem with filename");

    auto ofe = OnyxFileElement();
    auto filelines = _loadFile(filename);
    _getName(filename, &ofe);
    _parseFile(filelines, &ofe);

    return ofe;
}

void _getName(LPCWSTR filename, OnyxFileElement* element)
{
    wcmatch resultsMatch;
    wregex rgxCarretLine = wregex(L".*?([A-ZА-Яa-zа-я0-9]{1,64})[.]{1,1}([A-Za-z]{1,12})");

    if (regex_match(filename, resultsMatch, rgxCarretLine))
    {
        element->Name = resultsMatch[1].str();
        element->Type = resultsMatch[2].str();
    }
}

vector<wstring> _loadFile(LPCWSTR filename)
{
    vector<wstring> filelines;
    wifstream in(filename);
    in.imbue(locale(".utf-8"));

    if (in.is_open())
    {
        std::wstring line;
        while (std::getline(in, line))
        {
            filelines.push_back(line);
        }
    }
    in.close();

    return filelines;
}

void _parseFile(vector<wstring> filelines, OnyxFileElement* ofe)
{
    wcmatch resultsMatch;

    for (size_t i = 0; i < filelines.size(); i++)
    {
        if (regex_match(filelines[i].c_str(), resultsMatch, rgxGroupLine))
        {
            auto _node = _parseNode(filelines, i);
            _node.Name = resultsMatch[1].str();
            ofe->Tree.push_back(_node);
        }
        else if (regex_match(filelines[i].c_str(), resultsMatch, rgxCarretLine))
        {
            auto _node = OnyxFileNode(resultsMatch[1].str(), resultsMatch[2].str());
            ofe->Tree.push_back(_node);
        }
        else if (regex_match(filelines[i].c_str(), resultsMatch, rgxVec3Line))
        {
            auto _node = OnyxFileNode(resultsMatch[1].str(), resultsMatch[2].str());
            ofe->Tree.push_back(_node);
        }
    }
}

#pragma region OutputMatchResult
/*wcout << L"---------------------------------------------------------------------" << endl;
for (size_t i = 0; i < filelines.size(); i++)
{
    if (regex_match(filelines[i].c_str(), resultsMatch, rgxGroupLine))
        //wcout << i << L" - \033[37;42mMATCH\033[0m\t| [" << resultsMatch[1] << L" - " << resultsMatch[2] << L"]" << endl;
        wcout << i << L" - \033[37;42mMATCH\033[0m\t| " << filelines[i].c_str() << endl;
    else if (regex_match(filelines[i].c_str(), resultsMatch, rgxBackwardCaret))
        //wcout << i << L" - \033[37;42mMATCH\033[0m\t| [" << resultsMatch[1] << L" - " << resultsMatch[2] << L"]" << endl;
        wcout << i << L" - \033[37;42mMATCH\033[0m\t| " << filelines[i].c_str() << endl;
    else
        wcout << i << L" - \033[37;41mNOT MATCH\033[0m\t| " << filelines[i].c_str() << endl;

    wcout << L"---------------------------------------------------------------------" << endl;
}*/
#pragma endregion

OnyxFileNode _parseNode(vector<wstring>& filelines, size_t& index)
{
    wcmatch resultsMatch;
    OnyxFileNode result = OnyxFileNode();

    for (index++; index < filelines.size(); index++)
    {
        if (regex_match(filelines[index].c_str(), resultsMatch, rgxForwardCaret))
        {

        }
        else if (regex_match(filelines[index].c_str(), resultsMatch, rgxGroupLine))
        {
            auto _node = _parseNode(filelines, index);
            _node.Name = resultsMatch[1].str();
            result.Tree.push_back(_node);
        }
        else if (regex_match(filelines[index].c_str(), resultsMatch, rgxCarretLine))
        {
            auto _node = OnyxFileNode(resultsMatch[1].str(), resultsMatch[2].str());
            result.Tree.push_back(_node);
        }
        else if (regex_match(filelines[index].c_str(), resultsMatch, rgxVec3Line))
        {
            auto _node = OnyxFileNode(resultsMatch[1].str(), resultsMatch[2].str());
            result.Tree.push_back(_node);
        }
        else if (regex_match(filelines[index].c_str(), resultsMatch, rgxBackwardCaret))
        {
            return result;
        }
    }
}