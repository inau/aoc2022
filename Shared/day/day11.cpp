#include "day11.h"
#include <sstream>
#include <vector>
#include <queue>
#include <set>
#include <functional>
#include <algorithm>

namespace AoC22 { namespace Days {


long long Monkey::m_globalDivisor = 1;

const unsigned int AoC22::Days::Day11::GetDay() const
{
	return 11u;
}

void LoadData(Jungle& jungle, std::ifstream& data, int worry = 1)
{
	std::vector<std::string> _lines;
	IterateData(data, [&](const std::string& line)
	{
		if (line.empty())
		{
			MonkeyParms parms = Monkey::ParseMonkey(_lines);
			parms.worryfactor = worry;
			Monkey::SpawnMonkey(&jungle, parms);
			_lines.clear();
		} 
		else
		{
			_lines.push_back(line);
		}
	});
	if (!_lines.empty())
	{
		MonkeyParms parms = Monkey::ParseMonkey(_lines);
		Monkey::SpawnMonkey(&jungle, parms);
		_lines.clear();
	}
}

std::shared_ptr<DayResult> AoC22::Days::Day11::_runFirst(std::ifstream& data)
{
	unsigned losCount = 0;
	
	Jungle jungle;
	LoadData(jungle, data, 3);

	auto Round = [&]()
	{
		for (int i = 0; i < jungle.size(); ++i)
		{
			jungle[i].InspectItem();
		}
	};

	for (int r = 0; r < 20; ++r)
	{
		Round();
	}

	int x = 0, y = 0;
	for (int i = 0; i < jungle.size(); ++i)
	{
		int in = jungle[i].GetInspections();
		if (in > x)
		{
			y = x;
			x = in;
		} else if(in > y)
		{
			y = in;
		}
	}

	return std::make_shared<DayIntegerResult>(x * y);
}

std::shared_ptr<DayResult> AoC22::Days::Day11::_runSecond(std::ifstream& data)
{
	Jungle jungle;
	LoadData(jungle, data, -1);

	auto Round = [&]()
	{
		for (int i = 0; i < jungle.size(); ++i)
		{
			jungle[i].InspectItem();
		}
	};

	for (int r = 0; r < 10000; ++r)
	{
		Round();
	}

	unsigned long long x = 0, y = 0;
	for (int i = 0; i < jungle.size(); ++i)
	{
		int in = jungle[i].GetInspections();
		if (in > x)
		{
			y = x;
			x = in;
		}
		else if (in > y)
		{
			y = in;
		}
	}

	return std::make_shared<DayBigIntegerResult>(x * y);
}

bool Monkey::TargetMonkey(const long long& value)
{
	return (value % m_divisor) == 0ull;
}

long long Monkey::NewItemValue(const long long& oldValue)
{
	return m_fn(oldValue);
}

void Monkey::Handoff(unsigned monkeyId, long long item)
{
	if (m_jungle && monkeyId < m_jungle->size())
	{
		m_jungle->at(monkeyId).Receive(item);
	}
}

void Monkey::Receive(int item)
{
	m_inventory.push(item);
}

Monkey::Monkey(Jungle* jungle, const MonkeyParms& params)
	: m_inspectionCount(0u)
	, m_jungle(jungle)
	, m_divisor(params.div) , m_fn(GetFunc(params.op, params.val))
	, m_mainTarget(params.main) , m_secondaryTarget(params.second)
	, m_worryFactor(params.worryfactor != 0 ? params.worryfactor : -1)
{
	//m_jungle = jungle;
	for (auto& i : params.items)
	{
		m_inventory.push(i);
	}
}

long long Monkey::GetCommon()
{
	long long res = 1;
	for(unsigned monkey = 0; m_jungle && monkey < m_jungle->size(); monkey++)
	{
		res *= m_jungle->at(monkey).m_divisor;
	}
	return res;
}

MonkeyFunc Monkey::GetFunc(char op, long long val)
{
	switch (op)
	{
	case '*': return [val](long long i) { return i * val; };
	case '+': return [val](long long i) { return i + val; };
	case '-': return [val](long long i) { return i - val; };
	case '/': return [val](long long i) { return val != 0 ? i / val : 0; };
	case '#': return [val](long long i) { return i * i; };
	default:  return [   ](long long i) { return 0; };
	}
}

void Monkey::InspectItem()
{
	if (m_worryFactor == -1)
	{
		if(m_globalDivisor == 1) m_globalDivisor = GetCommon();
	}

	while (!m_inventory.empty())
	{
		long long item = m_worryFactor != -1 
			? NewItemValue(m_inventory.front()) / m_worryFactor 
			: NewItemValue(m_inventory.front()) % m_globalDivisor;
		m_inventory.pop();
		m_inspectionCount++;
		if (TargetMonkey(item))
		{
			Handoff(m_mainTarget, item);
		}
		else
		{
			Handoff(m_secondaryTarget, item);
		}
	}
}

unsigned long long Monkey::GetInspections()
{
	return m_inspectionCount;
}

void Monkey::SpawnMonkey(Jungle* jungle, const MonkeyParms& params)
{
	if (jungle)
	{
		jungle->emplace_back(std::move(Monkey(jungle, params)));
	}
}

void ReadItems(std::string& str, MonkeyParms& out) 
{
	std::stringstream ss(str);

	std::string tmp;
	while (ss >> tmp && tmp != "items:") {}

	char c;
	int i;
	while(ss >> i) 
	{ 
		out.items.push_back(i); 
		ss >> c; // ','
	}

};

void ReadOp(std::string& str, MonkeyParms& out)
{
	std::stringstream ss(str);

	std::string tmp;
	while (ss >> tmp && tmp != "old") {}
	char c;
	int i;
	if (ss >> c) { out.op = c;  }
	if (ss >> tmp)
	{
		if(tmp == "old") out.op = '#';
		else out.val = std::stoi(tmp.c_str()); 
	}

};

void ReadTest(std::string& str, MonkeyParms& out)
{
	std::stringstream ss(str);

	std::string tmp;
	while (ss >> tmp && tmp != "by") {}
	int i;
	if (ss >> i) { out.div = i; }
};

void ReadMonkeyTarget(std::string& str, unsigned int& out)
{
	std::stringstream ss(str);

	std::string tmp;
	while (ss >> tmp && tmp != "monkey") {}
	int i;
	if (ss >> i) { out = i; }
};

MonkeyParms Days::Monkey::ParseMonkey(std::vector<std::string>& monkeyText)
{
	MonkeyParms parms;
	parms.worryfactor = 1;
	ReadItems(monkeyText[1], parms);
	ReadOp(monkeyText[2], parms);
	ReadTest(monkeyText[3], parms);
	ReadMonkeyTarget(monkeyText[4], parms.main);
	ReadMonkeyTarget(monkeyText[5], parms.second);

	return parms;
}

}}