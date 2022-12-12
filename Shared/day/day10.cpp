#include "day10.h"
#include <sstream>
#include <vector>
#include <queue>
#include <set>
#include <functional>
#include <algorithm>

namespace AoC22 { namespace Days {

const unsigned int AoC22::Days::Day10::GetDay() const
{
	return 10u;
}

/// <summary>

class Instruction
{
protected:
	virtual ~Instruction() {};
public:
	const unsigned Cycles;
	enum class Type 
	{
		Unknown,
		Noop,
		Addx
	};
	Instruction(int c) : Cycles(c) {}

public:
	static Type ParseType(const std::string& txt)
	{
		Type t = Type::Unknown;
		
		if (txt == "noop") t = Type::Noop;
		else if (txt == "addx") t = Type::Addx;
		else {}

		return t;
	}
	static std::shared_ptr<Instruction> CreateInstruction(Type t, int value = 0);
};

class Noop : public Instruction
{
public:
	Noop() : Instruction(1) {}
};

class Addx : public Instruction
{
public:
	const int x;

	Addx(int y) : Instruction(2), x(y) {};
};

std::shared_ptr<Instruction> Instruction::CreateInstruction(Type type, int value)
{
	switch (type)
	{
	case AoC22::Days::Instruction::Type::Noop: return std::make_shared<Noop>(); 
	case AoC22::Days::Instruction::Type::Addx: return std::make_shared<Addx>(value);
	case AoC22::Days::Instruction::Type::Unknown:
	default:
		return nullptr;
	}
};

class InstructionHandler
{
protected:
	long X;
	long C;

	void Process(Instruction* instr, int& cycles, int& postVal)
	{
		postVal = 0;

		Addx* addFn = dynamic_cast<Addx*>(instr);
		if (addFn)
		{
			postVal = addFn->x;
		}
		cycles = instr ? instr->Cycles : 0;
	};
	
	long GetResult() { return C * X; }
public:
	std::string ProcessCRT(std::vector<std::shared_ptr<Instruction>> _instr, std::string CRT)
	{
		long total = 0;
		X = 1;
		C = 0;
		int _c = 0;
		int _v = 0;
		auto GetPx = [&](int C)
		{
			int __c = C % 40;
			int __x = X % 40;
			return ( (__x -1) <= __c && __c <= (__x+1) ) ? '#' : '.';
		};
		for (auto& ptr : _instr)
		{
			if (ptr)
			{
				Process(ptr.get(), _c, _v);
				for (unsigned c = 0; c < _c; c++, C++)
				{
					if (C < CRT.size())
					{
						CRT[C] = GetPx(C);
					}
				}
				X += _v;
			}
		}
		if (C < CRT.size())
		{
			CRT[C] = GetPx(C);
		}

		return CRT;
	}
	
	long Process(std::vector<std::shared_ptr<Instruction>> _instr, std::pair<unsigned,unsigned> cycleMultInfo)
	{
		long total = 0;
		X = 1;
		C = 0;
		int _c = 0;
		int _v = 0;
		long NextMult = cycleMultInfo.first;
		for (auto& ptr : _instr)
		{
			if (ptr)
			{
				Process(ptr.get(), _c, _v);
				for (unsigned c = 0; c < _c; c++)
				{
					C++;
					if (C == NextMult)
					{
						total += GetResult();
						NextMult += cycleMultInfo.second;
					}
				}
				X += _v;
			}
		}

		if (C == NextMult)
		{
			total += GetResult();
			NextMult += cycleMultInfo.second;
		}

		return total;
	}
};

std::vector<std::shared_ptr<Instruction>> GetInstructions(std::ifstream& data)
{
	std::vector<std::shared_ptr<Instruction>> _instr;

	IterateData(data, [&_instr](const std::string& line)
	{
		std::stringstream stream(line);
		std::string command;
		int value = 0;
		if (stream >> command)
		{
			Instruction::Type type = Instruction::ParseType(command);
			
			if(type == Instruction::Type::Addx)
			{
				stream >> value;
			}
			_instr.push_back(Instruction::CreateInstruction(type, value));
		}
	});

	return _instr;
}

/// <summary>


std::shared_ptr<DayResult> AoC22::Days::Day10::_runFirst(std::ifstream& data)
{
	long result = 0;

	auto inst = GetInstructions(data);
	InstructionHandler handler;
	result = handler.Process(inst, std::make_pair(20,40));
	return std::make_shared<DaySignedIntegerResult>(result);
}



std::shared_ptr<DayResult> AoC22::Days::Day10::_runSecond(std::ifstream& data)
{
	std::string crt;
	crt.resize(240);
	auto inst = GetInstructions(data);
	InstructionHandler handler;
	crt = handler.ProcessCRT(inst, crt);

	return std::make_shared<DayStringResult>(crt);
}

}}