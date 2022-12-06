#include "day05.h"
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>

namespace AoC22 { namespace Days {

const unsigned int AoC22::Days::Day05::GetDay() const
{
	return 5u;
}

struct Command
{
	unsigned cnt, src, target;
	Command(unsigned n, unsigned min, unsigned max)
		:src(min)
		,cnt(n)
		,target(max) {}
};

Command DecodeCommand(const std::string& str)
{
	std::stringstream buff(str);

	std::string dummy;
	int n, s, t;
	if (   buff >> dummy
		&& buff >> n
		&& buff >> dummy
		&& buff >> s
		&& buff >> dummy
		&& buff >> t
	)
	{
		return Command(n, s, t);
	}

	return Command(0, 0, 0);
}

void LoadData(std::ifstream& data, std::vector<std::deque<char>>& stacks, std::vector<Command>& commands)
{
	std::string line;
	while (std::getline(data, line))
	{
		if (stacks.empty())
		{
			unsigned N = (line.size() + 1) / 4;
			stacks.resize(N);
		}

		if (line.find("move ") != line.npos)
		{
			commands.push_back(DecodeCommand(line));
		}
		else
		{
			for (unsigned c = 0, col = 0u; c < line.size(); c += 4, col++)
			{
				if (line[c] == '[')
				{
					stacks[col].push_front(line[c + 1]);
				}
			}
		}
	}
}

std::shared_ptr<DayResult> AoC22::Days::Day05::_runFirst(std::ifstream& data)
{
	std::vector<std::deque<char>> stacks;
	std::vector<Command> commands;

	LoadData(data, stacks, commands);

	/// Process command queue
	for (auto& cmd : commands)
	{
		auto& src = stacks[cmd.src-1];
		auto& tar = stacks[cmd.target-1];

		for (int c = 0; c < cmd.cnt; c++)
		{
			tar.push_back(src.back());
			src.pop_back();
		}
	}

	std::string result;
	for(auto& stk : stacks)
	{
		result += stk.back();
	}

	return std::make_shared<DayStringResult>(result);
}



std::shared_ptr<DayResult> AoC22::Days::Day05::_runSecond(std::ifstream& data)
{
	std::vector<std::deque<char>> stacks;
	std::vector<Command> commands;

	LoadData(data, stacks, commands);

	/// Process command queue
	for (auto& cmd : commands)
	{
		auto& src = stacks[cmd.src - 1];
		auto& tar = stacks[cmd.target - 1];

		std::vector<char> _chars;
		_chars.resize(cmd.cnt);
		for (int c = 0; c < cmd.cnt; c++)
		{
			_chars[(cmd.cnt-1) - c] = src.back();
			src.pop_back();
		}
		for (auto& cc : _chars)
		{
			tar.push_back(cc);
		}
	}

	std::string result;
	for (auto& stk : stacks)
	{
		result += stk.back();
	}

	return std::make_shared<DayStringResult>(result);
}

}}