#pragma once
#include <string>
#include <queue>
#include "dayShared.h"
#include "../io/dataInstance.h"

namespace AoC22 { namespace Days {

	class Day11 : public Day
	{
	protected:
		// Inherited via Day
		virtual std::shared_ptr<DayResult> _runFirst(std::ifstream& data) override;
		virtual std::shared_ptr<DayResult> _runSecond(std::ifstream& data) override;

		virtual const unsigned int GetDay() const override;
	public:
		Day11(IO::InputDataReader& reader) : Day(reader) {};
	};

	class Monkey;
	struct MonkeyParms
	{
		int worryfactor;

		std::vector<int> items;
		
		char op;
		int val;

		unsigned int div;
		unsigned int main;
		unsigned int second;
	};

	//class Jungle
	//{
	//protected:
	//	std::vector<Monkey> m_jungle;
	//
	//public:
	//	void SpawnMonkey(const MonkeyParms& params);
	//	static MonkeyParms ParseMonkey(std::vector<std::string>& monkeyText);
	//	
	//	std::vector<Monkey>& GetJungle();
	//};

	typedef std::vector<Monkey> Jungle;
	typedef std::queue<long long> Inventory;

	typedef std::function<long long(long long)> MonkeyFunc;


	class Monkey
	{
	protected:
		static long long m_globalDivisor;
		Jungle* m_jungle;

		unsigned long long m_inspectionCount;
		Inventory m_inventory;

		MonkeyFunc m_fn;
//		const int m_multiplier;
		const long long m_divisor;
		long long m_worryFactor;
		
		const unsigned m_mainTarget;
		const unsigned m_secondaryTarget;

		bool TargetMonkey(const long long& oldValue);
		long long NewItemValue(const long long& oldValue);
		void Handoff(unsigned monkeyId, long long item);
		void Receive(int item);

		Monkey(Jungle* jungle, const MonkeyParms& params);

		long long GetCommon();
		static MonkeyFunc GetFunc(char op, long long val);
	public:
		void InspectItem();
		unsigned long long GetInspections();

		static void SpawnMonkey(std::vector<Monkey>* jungle, const MonkeyParms& params);
		static MonkeyParms ParseMonkey(std::vector<std::string>& monkeyText);
	};

}}
