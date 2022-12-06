#pragma once
#include <io/reader.h>

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

	static std::wstring WideStr(unsigned int type)
	{
		return Shared::WideStr(std::to_wstring(type));
	}
};