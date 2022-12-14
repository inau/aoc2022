#pragma once
#include <string>
#include <functional>
#include "../io/reader.h"
#include "../day/dayresults.h"

namespace AoC22 { namespace Days {


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
		std::shared_ptr<DayResult> runSecond(bool exampleInput, unsigned auxindex = 0u);
	};

	void IterateData(std::ifstream& data, std::function<void(const std::string&)> LineFunc);

}}
