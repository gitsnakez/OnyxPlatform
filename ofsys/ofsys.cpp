#include "ofsys.h"

EXTERN API HRESULT CheckIsFileExsits(LPCWSTR filename, LPCWSTR* msg, bool ShowMsgBox)
{
    auto textinfo = std::wstringstream();
    std::ifstream file;
    file.open(filename);
    file.imbue(std::locale(".utf-8"));

    if (!file.is_open())
    {
        textinfo << filename << L" - doesn't found!";
        *msg = textinfo.str().c_str();

        if(ShowMsgBox)
            MessageBox(NULL, L"Onyx File System", textinfo.str().c_str(), MB_OK);

        return S_FALSE;
    }
    *msg = L"found";

    return S_OK;
}
