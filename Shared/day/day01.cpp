#include "day01.h"
#include <sstream>

namespace AoC22 { namespace Days {

const unsigned int AoC22::Days::Day01::GetDay() const
{
	return 1u;
}

std::shared_ptr<DayResult> AoC22::Days::Day01::_runFirst(std::ifstream& data)
{
	unsigned int result = 0;

	int dummy = 0;
	int tmpsum = 0;
	std::string line;
	std::stringstream lineBuffer;
	
	while ( std::getline(data,line) )
	{
		if (line.empty()) // finish sum
		{
			result = result < tmpsum ? tmpsum : result;
			tmpsum = 0;
		}
		else if(lineBuffer << line && lineBuffer >> dummy)
		{
			tmpsum += dummy;
		}
		lineBuffer.clear();
	}

	return std::make_shared<DayIntegerResult>(result);
}

std::shared_ptr<DayResult> AoC22::Days::Day01::_runSecond(std::ifstream& data)
{
	unsigned int result[3] = { 0 };

	int dummy = 0;
	int tmpsum = 0;
	std::string line;
	std::stringstream lineBuffer;

	auto UpdateResult = [&](const int& tmp)
	{
		if (tmpsum > result[1])
		{
			if (tmpsum > result[0])
			{
				// push down
				result[2] = result[1];
				result[1] = result[0];
				result[0] = tmpsum;
			}
			else
			{
				result[2] = result[1];
				result[1] = tmpsum;
			}
		}
		else
		{
			if (tmpsum > result[2])
			{
				result[2] = tmpsum;
			}
		}

		tmpsum = 0;
	};

	while (std::getline(data, line))
	{
		if (line.empty()) // finish sum
		{
			UpdateResult(tmpsum);
		}
		else if (lineBuffer << line && lineBuffer >> dummy)
		{
			tmpsum += dummy;
		}
		lineBuffer.clear();
	}
	UpdateResult(tmpsum);

	tmpsum += result[0];
	tmpsum += result[1];
	tmpsum += result[2];

	return std::make_shared<DayIntegerResult>(tmpsum);
}

}}