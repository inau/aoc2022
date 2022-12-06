#pragma once
#include <string>
#include "../io/reader.h"

namespace AoC22 { namespace Days {

	class DayResult
	{
	public:
		virtual ~DayResult() {}
	};

	class DayIntegerResult : public DayResult
	{
	public:
		DayIntegerResult(unsigned int _val) : Value(_val) {}
		const unsigned int Value;
	};

	class DayStringResult : public DayResult
	{
	public:
		DayStringResult(std::string _val) : Value(_val +"\n") {}
		std::string Value;
	};

	class Day
	{
	protected:
		virtual const unsigned int GetDay() const = 0;

		IO::InputDataReader& m_input;

		virtual std::shared_ptr<DayResult> _runFirst(std::ifstream& data) = 0;
		virtual std::shared_ptr<DayResult> _runSecond(std::ifstream& data) = 0;

	public:
		Day(IO::InputDataReader& reader);

		std::shared_ptr<DayResult> runFirst(bool exampleInput);
		std::shared_ptr<DayResult> runSecond(bool exampleInput);
	};



}}
