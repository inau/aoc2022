#pragma once
#include <string>
#include "dayShared.h"
#include "../io/dataInstance.h"

namespace AoC22 { namespace Days {

	class Day09 : public Day
	{
	protected:
		// Inherited via Day
		virtual std::shared_ptr<DayResult> _runFirst(std::ifstream& data) override;
		virtual std::shared_ptr<DayResult> _runSecond(std::ifstream& data) override;

		virtual const unsigned int GetDay() const override;
	public:
		Day09(IO::InputDataReader& reader) : Day(reader) {};
	};


}}
