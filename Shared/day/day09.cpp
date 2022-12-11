#include "day09.h"
#include <sstream>
#include <vector>
#include <queue>
#include <set>
#include <functional>
#include <algorithm>

namespace AoC22 { namespace Days {

	typedef std::pair<int, int> Coord;

const unsigned int AoC22::Days::Day09::GetDay() const
{
	return 9u;
}

int GetDirection(char c, int cnt)
{
	int nb = 0;
	switch (c)
	{
	case 'R':
	case 'U':
	{
		nb = cnt; break;
	}
	case 'L':
	case 'D':
	{
		nb = -cnt; break;
	}
	}
	return nb;
}

Coord GetDirectionVector(char c, int cnt)
{
	switch (c)
	{
	case 'R':
	case 'L':
	{
		return std::make_pair(GetDirection(c,cnt), 0);
	} break;
	case 'U':
	case 'D':
	{
		return std::make_pair(0, GetDirection(c, cnt));
	} break;
	}
	return std::make_pair(0, 0);
}

Coord GetMoveVector(const Coord& primary, const Coord& secondary)
{
	return Coord(primary.first - secondary.first, primary.second - secondary.second);
}

bool hasToMove(const Coord& primary, const Coord& secondary)
{
	auto [xd, yd] = GetMoveVector(primary, secondary);
	return (std::abs(xd) > 1) || (std::abs(yd) > 1);
}

void Move(Coord& primary, const Coord& move)
{
	int xs = move.first != 0 ? 1 : 0;
	int ys = move.second != 0 ? 1 : 0;
	primary.first += (move.first > 0 ? +xs : -xs);
	primary.second += (move.second > 0 ? +ys : -ys);
}

std::string DrawString(std::set<Coord>& coords, int gridSz)
{
	std::stringstream outStrm;
	std::string line;
	line.resize(gridSz, '.');

	Coord c;
	for (int y = gridSz; y >= 0; --y)
	{
		for (int x = 0; x < gridSz; ++x)
		{
			c.first = x;
			c.second = y;
			if (coords.count(c) > 0)
			{
				line[x] = '#';
			}
			else 
				line[x] = '.';
		}

		outStrm << line << std::endl;
	}

	return outStrm.str();
}

std::set<Coord> GetVisitedMap(std::ifstream& data, std::vector<Coord>& rope)
{
	if (rope.size() < 1) throw std::exception("Rope to short");

	Coord& head = rope.front();
	std::set<Coord> _moves;
	_moves.insert(rope.back());
	auto MoveLogic = [&]()
	{
		for (int r = 1; r < rope.size(); ++r)
		{
			Coord& knotHead = rope[r - 1];
			Coord& knotTail = rope[r];
			if (hasToMove(knotHead,knotTail))
			{
				auto move = GetMoveVector(knotHead, knotTail);
				Move(knotTail, move);
			}
		}
		_moves.insert(rope.back());
	};

	char dir;
	int cnt;
	IterateData(data, [&](const std::string& str)
	{
		std::stringstream stream(str);
		if (stream >> dir && stream >> cnt)
		{
			auto [xx, yy] = GetDirectionVector(dir,cnt);
			int xs = xx < 0 ? -1 : 1;
			int ys = yy < 0 ? -1 : 1;
			for (int x = 0; x < std::abs(xx); ++x)
			{
				head.first += xs;
				MoveLogic();
			}
			for (int y = 0; y < std::abs(yy); ++y)
			{
				head.second += ys;
				MoveLogic();
			}

		}
	});

	auto strMap = DrawString(_moves, 20);

	return _moves;
}

std::vector<Coord> CreateRope(unsigned length)
{
	std::vector<Coord> _rope;
	_rope.resize(length, std::make_pair(0, 0));
	return _rope;
}

std::shared_ptr<DayResult> AoC22::Days::Day09::_runFirst(std::ifstream& data)
{
	unsigned losCount = 0;

	auto _rope = CreateRope(2);
	auto tailPositions = GetVisitedMap(data, _rope);

	return std::make_shared<DayIntegerResult>(tailPositions.size());
}



std::shared_ptr<DayResult> AoC22::Days::Day09::_runSecond(std::ifstream& data)
{
	unsigned int bestScene = 0u;

	auto _rope = CreateRope(10);
	auto tailPositions = GetVisitedMap(data, _rope);

	return std::make_shared<DayIntegerResult>(tailPositions.size());
}



}}