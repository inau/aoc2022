#pragma once
#include <io/reader.h>
#include <Windows.h>

namespace Shared
{
	constexpr wchar_t* InputDataRoot = L"E:/Workspaces/cpp/AdventOfCode/aoc2022/InputData/";
	constexpr wchar_t* FirstAssignmentStr = L"First";
	constexpr wchar_t* SecondAssignmentStr = L"second";
	
	static AoC22::IO::InputDataReader InputInstance()
	{
		static AoC22::IO::InputDataReader instance(Shared::InputDataRoot);
		return instance;
	}

	static std::wstring GetName(unsigned int day, std::wstring type)
	{
		return std::wstring(L"Day_") + std::to_wstring(day) + L"_" + type + L'\n';
	}
	

	static std::wstring WideStr(std::wstring type)
	{
		return type + L'\n';
	}

	static std::wstring WideStr(std::string str)
	{
		std::wstring result;
		int cvtResult = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.size(), nullptr, 0);
		if (cvtResult > 0)
		{
			result.resize(cvtResult + 10);
			cvtResult = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.size(), &result[0], result.size());
		}
		return result;
	}

	static std::wstring WideStrUL(unsigned long long type)
	{
		return Shared::WideStr(std::to_wstring(type));
	}

	static std::wstring WideStr(unsigned int type)
	{
		return Shared::WideStr(std::to_wstring(type));
	}
};