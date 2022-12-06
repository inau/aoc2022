#include "day03.h"
#include <sstream>
#include <map>
#include <set>
#include <array>

namespace AoC22 { namespace Days {

const unsigned int AoC22::Days::Day03::GetDay() const
{
	return 3u;
}

int CharScore(char c)
{
	if ('a' <= c && c <= 'z') return 1 + ((int)c - 'a');
	else if ('A' <= c && c <= 'Z') return 27 + ((int)c - 'A');
	return 0;
}

std::shared_ptr<DayResult> AoC22::Days::Day03::_runFirst(std::ifstream& data)
{
	int result = 0;

	std::string line;
	
	std::set<char> lhs,rhs,dupl;
	char c;
	while ( std::getline(data,line) )
	{
		int pivot = line.size() / 2;
		for (int i = 0; i < pivot; ++i)
		{
			lhs.insert(line[i]);
			rhs.insert(line[pivot+i]);
		}

		for(auto& var : lhs)
		{
			if (rhs.find(var) != rhs.end())
			{
				dupl.insert(var);
				result += CharScore(var);
			}
		}
		lhs.clear();
		rhs.clear();
	}

	return std::make_shared<DayIntegerResult>(result);
}

std::shared_ptr<DayResult> AoC22::Days::Day03::_runSecond(std::ifstream& data)
{
	int result = 0;

	std::array<std::string, 3> line;
	std::array<char, 3> masks =	{ 0x01, 0x02, 0x04 };
	std::map<char, char> backpack;
	int c = 0u;
	while (std::getline(data, line.at(c++ % 3)) )
	{
		if ((c % 3) == 0) // 3 lines loaded
		{
			for (int j = 0; j < line.size(); ++j)
			{
				for (auto& l : line.at(j))
				{
					backpack[l] |= masks[j];
				}
			}

			for (auto& kv : backpack)
			{
				if (kv.second == 7) result += CharScore(kv.first);
			}

			backpack.clear();
		}
	}

	return std::make_shared<DayIntegerResult>(result);
}

}}