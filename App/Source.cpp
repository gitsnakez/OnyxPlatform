#include <Windows.h>

bool LoadDLL(const wchar_t* path, HMODULE* hMod) {
	HMODULE hLib;
	hLib = LoadLibrary(path);

	if (!hLib)
		return false;

	hMod = &hLib;
	return true;
}

void CallFuncDLL(LPCSTR funcName, HMODULE* hMod) {
	void (*pFunction)(int, int);
	(FARPROC&)pFunction = GetProcAddress(*hMod, funcName);
	pFunction(0, 0);
}

int main() {
	HMODULE engineDll;

	if (!LoadDLL(L"OnyxDX.dll", &engineDll)){
		MessageBox(NULL, L"Engine load fail!", L"Application", MB_OK);
		return 0;
	}

	CallFuncDLL("StartEngine", &engineDll);

	return 0;
}