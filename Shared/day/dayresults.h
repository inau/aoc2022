#pragma once
#include <string>
#include <functional>
#include "../io/reader.h"

namespace AoC22 { namespace Days {

	class DayResult
	{
	public:
		virtual ~DayResult() {}
	};

	class DayBigIntegerResult : public DayResult
	{
	public:
		DayBigIntegerResult(unsigned long long _val) : Value(_val) {}
		const unsigned long long Value;
	};

	class DayIntegerResult : public DayResult
	{
	public:
		DayIntegerResult(unsigned int _val) : Value(_val) {}
		const unsigned int Value;
	};

	class DaySignedIntegerResult : public DayResult
	{
	public:
		DaySignedIntegerResult(int _val) : Value(_val) {}
		const int Value;
	};

	class DayStringResult : public DayResult
	{
	public:
		DayStringResult(std::string _val) : Value(_val +"\n") {}
		std::string Value;
	};

}}
