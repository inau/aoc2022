#include "day04.h"
#include <sstream>
#include <vector>
#include <algorithm>

namespace AoC22 { namespace Days {

const unsigned int AoC22::Days::Day04::GetDay() const
{
	return 4u;
}

struct Range
{
	unsigned lo, hi;
	Range(unsigned min, unsigned max)
		:lo(min)
		,hi(max) {}
};

bool rangeInside(const Range& lhs, const Range& rhs)
{
	return (lhs.lo <= rhs.lo && rhs.lo <= lhs.hi)
		|| (lhs.lo <= rhs.hi && rhs.hi <= lhs.hi);
}

bool rangeContains(const Range& lhs, const Range& rhs)
{
	return (lhs.lo <= rhs.lo && lhs.hi >= rhs.hi);
}

std::shared_ptr<DayResult> AoC22::Days::Day04::_runFirst(std::ifstream& data)
{
	int result = 0;

	std::string line;
	std::stringstream lineBuffer;
	std::vector<Range> ranges;
	char dummy;
	int min, max;
	while ( std::getline(data,line) )
	{
		if (lineBuffer << line)
		{
			lineBuffer >> min;
			lineBuffer >> dummy;
			lineBuffer >> max;
			lineBuffer >> dummy;
			ranges.emplace_back(min, max);
			lineBuffer >> min;
			lineBuffer >> dummy;
			lineBuffer >> max;
			ranges.emplace_back(min, max);
		}

		lineBuffer.clear();
	}

	for (unsigned r = 0; r < ranges.size(); r+=2)
	{
		Range lhs = ranges[r];
		Range rhs = ranges[r+1];
		if (rangeContains(lhs, rhs) || rangeContains(rhs, lhs)) result++;
	}

	return std::make_shared<DayIntegerResult>(result);
}



std::shared_ptr<DayResult> AoC22::Days::Day04::_runSecond(std::ifstream& data)
{
	int result = 0;

	std::string line;
	std::stringstream lineBuffer;
	std::vector<Range> ranges;
	char dummy;
	int min, max;
	while (std::getline(data, line))
	{
		if (lineBuffer << line)
		{
			lineBuffer >> min;
			lineBuffer >> dummy;
			lineBuffer >> max;
			lineBuffer >> dummy;
			ranges.emplace_back(min, max);
			lineBuffer >> min;
			lineBuffer >> dummy;
			lineBuffer >> max;
			ranges.emplace_back(min, max);
		}

		lineBuffer.clear();
	}

	for (unsigned r = 0; r < ranges.size(); r += 2)
	{
		Range lhs = ranges[r];
		Range rhs = ranges[r + 1];
		if (rangeInside(lhs, rhs) || rangeInside(rhs, lhs)) result++;
	}

	return std::make_shared<DayIntegerResult>(result);
}
//std::shared_ptr<DayResult> AoC22::Days::Day04::_runSecond(std::ifstream& data)
//{
//	int result = 0;
//	std::string line;
//	std::stringstream lineBuffer;
//	std::vector<Range> ranges;
//	char dummy;
//	int min, max;
//	while (std::getline(data, line) )
//	{
//		if (lineBuffer << line)
//		{
//			lineBuffer >> min;
//			lineBuffer >> dummy;
//			lineBuffer >> max;
//			lineBuffer >> dummy;
//			ranges.emplace_back(min, max);
//			lineBuffer >> min;
//			lineBuffer >> dummy;
//			lineBuffer >> max;
//			ranges.emplace_back(min, max);
//		}
//
//		lineBuffer.clear();
//	}
//
//	// sort ranges based on min
//	std::sort(ranges.begin(), ranges.end(),
//		[](const Range& lhs, const Range& rhs) { return lhs.lo < rhs.lo&& lhs.hi < rhs.hi; });
//
//	// process ranges
//	for (unsigned r = 0; r < ranges.size(); r++)
//	{
//		Range& lhs = ranges[r];
//		for (unsigned p = r + 1; p < ranges.size(); p++)
//		{
//			Range& rhs = ranges[p];
//
//			if (lhs.hi <= rhs.lo) break;
//
//			if (rangeInside(lhs,rhs)) result++;
//		}
//	}
//
//	return std::make_shared<DayIntegerResult>(result);
//}

}}