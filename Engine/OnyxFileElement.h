#pragma once

#include <string>
#include <vector>

using namespace std;

struct OnyxFileNode
{
public:
	OnyxFileNode() {}
	OnyxFileNode(wstring name, wstring value)
	{ Name = name; Value = value; }

	OnyxFileNode GetNodeByName(LPCWSTR name)
	{
		for (size_t i = 0; i < Tree.size(); i++)
		{
			if (name == Tree[i].Name)
				return Tree[i];
		}

		return OnyxFileNode(L"ERROR", L"ERROR");
	}

	std::wstring GetValueByName(LPCWSTR name)
	{
		for (size_t i = 0; i < Tree.size(); i++)
		{
			if (name == Tree[i].Name)
				return Tree[i].Value;
		}

		return L"ERROR NOT FOUND";
	}

	wstring Name;
	wstring Value;
	vector<OnyxFileNode> Tree;
};

struct OnyxFileElement
{
	OnyxFileNode GetNodeByName(LPCWSTR name)
	{
		for (size_t i = 0; i < Tree.size(); i++)
		{
			if (name == Tree[i].Name)
				return Tree[i];
		}

		return OnyxFileNode(L"ERROR", L"ERROR");
	}

	std::wstring GetValueByName(LPCWSTR name)
	{
		for (size_t i = 0; i < Tree.size(); i++)
		{
			if (name == Tree[i].Name)
				return Tree[i].Value;
		}

		return L"ERROR NOT FOUND";
	}

public:
	wstring Name;
	wstring Type;
	vector<OnyxFileNode> Tree;
};