#include "day02.h"
#include <sstream>

namespace AoC22 { namespace Days {

const unsigned int AoC22::Days::Day02::GetDay() const
{
	return 2u;
}

std::shared_ptr<DayResult> AoC22::Days::Day02::_runFirst(std::ifstream& data)
{
	int result = 0;

	std::string line;
	std::stringstream lineBuffer;
	
	char lhs, rhs;
	Token _lhs, _rhs;
	Outcome _score;
	while ( std::getline(data,line) )
	{
		if(lineBuffer << line && lineBuffer >> lhs && lineBuffer >> rhs)
		{
			_lhs = GetToken(lhs);
			_rhs = GetToken(rhs);
			_score = GetOutcome(_rhs, _lhs);
			result += (int) _score + (int) _rhs;
		}
		lineBuffer.clear();
	}

	return std::make_shared<DayIntegerResult>(result);
}

std::shared_ptr<DayResult> AoC22::Days::Day02::_runSecond(std::ifstream& data)
{
	int result = 0;

	std::string line;
	std::stringstream lineBuffer;

	char lhs, rhs;
	Token _lhs, _rhs;
	Outcome _score;
	while (std::getline(data, line))
	{
		if (lineBuffer << line && lineBuffer >> lhs && lineBuffer >> rhs)
		{
			_lhs = GetToken(lhs);
			_rhs = GetTokenForOutcome(_lhs, GetOutcome(rhs));
			_score = GetOutcome(_rhs, _lhs);

			result += (int)_score + (int)_rhs;
		}
		lineBuffer.clear();
	}

	return std::make_shared<DayIntegerResult>(result);
}

}}