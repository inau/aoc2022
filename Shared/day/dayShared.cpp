#include "dayShared.h"

namespace AoC22 { namespace Days {

Day::Day(IO::InputDataReader& reader)
	: m_input(reader)
{
}

std::shared_ptr<DayResult> Day::runFirst(bool exampleInput)
{
	return _runFirst(m_input
		.GetData(GetDay(), 
			exampleInput 
			? IO::DataInstance::Type::EXAMPLE 
			: IO::DataInstance::Type::INPUT)
		.getStream());
}

std::shared_ptr<DayResult> Day::runSecond(bool exampleInput)
{
	return _runSecond(m_input
		.GetData(GetDay(), 
			exampleInput 
			? IO::DataInstance::Type::EXAMPLE
			: IO::DataInstance::Type::INPUT)
		.getStream());
}

void IterateData(std::ifstream& data, std::function<void(const std::string&)> LineFunc)
{
	std::string line;
	while (std::getline(data, line) && LineFunc)
	{
		LineFunc(line);
	}
}


}}