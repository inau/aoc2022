#include "day06.h"
#include <sstream>
#include <vector>
#include <queue>
#include <set>
#include <functional>
#include <algorithm>

namespace AoC22 { namespace Days {

const unsigned int AoC22::Days::Day06::GetDay() const
{
	return 6u;
}

bool Compare(const std::string& str, unsigned start, unsigned count)
{
	std::set<char> _chars;
	for (unsigned s = start; s < (start+count) && s < str.size(); s++)
	{
		_chars.insert(str[s]);
	}
	return _chars.size() == count;
}

std::shared_ptr<DayResult> AoC22::Days::Day06::_runFirst(std::ifstream& data)
{
	unsigned cc = 4;

	std::vector<int> _index;
	auto func = [&cc, &_index](const std::string& line)
	{
		const unsigned idx = cc - 1;
		for (int i = idx; i < line.size(); ++i)
		{
			if( Compare(line,i-idx,cc) )
			{
				_index.push_back(i+1);
				break;
			}
		}
	};

	IterateData(data, func);

	/// Process command queue
	
	return std::make_shared<DayIntegerResult>(_index[0]);
}



std::shared_ptr<DayResult> AoC22::Days::Day06::_runSecond(std::ifstream& data)
{
	unsigned cc = 14;

	std::vector<int> _index;
	auto func = [&cc, &_index](const std::string& line)
	{
		const unsigned idx = cc - 1;
		for (int i = idx; i < line.size(); ++i)
		{
			if (Compare(line, i - idx, cc))
			{
				_index.push_back(i + 1);
				break;
			}
		}
	};

	IterateData(data, func);

	/// Process command queue

	return std::make_shared<DayIntegerResult>(_index[0]);
}

}}