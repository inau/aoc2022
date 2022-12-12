#include "CppUnitTest.h"
#include "SharedConstants.h"
#include "day/day10.h"
#include <functional>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AoC22;
using AoC22::IO::DataInstance;

namespace TestLibrary
{
	TEST_CLASS(TestLibrary_Day_10)
	{
	protected:
		AoC22::IO::InputDataReader& input = Shared::InputInstance();

		template<class T>
		std::pair<T*, std::shared_ptr<Days::DayResult> > UnwrapResult(std::function<std::shared_ptr<Days::DayResult>()> func)
		{
			auto baseresultEx = func();
			return std::make_pair(dynamic_cast<T*>(baseresultEx.get()), baseresultEx);
		}

	public:

		TEST_METHOD(First)
		{
			Days::Day10 day(input);

			auto resultEx = UnwrapResult<Days::DaySignedIntegerResult>(
				[&day]() { return day.runFirst(true);
			});

			Assert::AreEqual(13140, resultEx.first->Value, L"Example data has wrong result");

			auto result = UnwrapResult<Days::DaySignedIntegerResult>(
				[&day]() { return day.runFirst(false);
			});

			Logger::WriteMessage(Shared::WideStr(resultEx.first->Value).c_str());
			Logger::WriteMessage(Shared::WideStr(result.first->Value).c_str());
		}

		TEST_METHOD(Second)
		{
			Days::Day10 day(input);

			auto resultEx = UnwrapResult<Days::DayStringResult>(
				[&day]() { return day.runSecond(true);
			});

			std::string expected 
				= "##..##..##..##..##..##..##..##..##..##.." \
				  "###...###...###...###...###...###...###." \
				  "####....####....####....####....####...." \
				  "#####.....#####.....#####.....#####....." \
				  "######......######......######......####" \
				  "#######.......#######.......#######.....\n";

			int colSz = 40;
			for (int r = 0; r < 5; r++)
			{
				std::string subExp = expected.substr(r*colSz,colSz);
				std::string subresult = resultEx.first->Value.substr(r * colSz, colSz);
				Assert::AreEqual(subExp, subresult, (L"Example data has wrong result on line " + std::to_wstring(r+1)).c_str());
			}

			Assert::AreEqual(expected.c_str(), resultEx.first->Value.c_str(), L"Example data has wrong result");

			auto result = UnwrapResult<Days::DayStringResult>(
				[&day]() { return day.runSecond(false);
			});


			Logger::WriteMessage(Shared::WideStr(resultEx.first->Value).c_str());
			Logger::WriteMessage(Shared::WideStr(result.first->Value).c_str());
		}
	};
}
