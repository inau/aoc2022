#include "dayXX.h"
#include <sstream>
#include <vector>
#include <queue>
#include <set>
#include <functional>
#include <algorithm>

namespace AoC22 { namespace Days {

const unsigned int AoC22::Days::DayXX::GetDay() const
{
	return 42u;
}

std::shared_ptr<DayResult> AoC22::Days::DayXX::_runFirst(std::ifstream& data)
{
	unsigned losCount = 0;

	return std::make_shared<DayIntegerResult>(losCount);
}



std::shared_ptr<DayResult> AoC22::Days::DayXX::_runSecond(std::ifstream& data)
{
	unsigned int bestScene = 0u;

	return std::make_shared<DayIntegerResult>(bestScene);
}

}}