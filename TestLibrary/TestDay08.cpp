#include "CppUnitTest.h"
#include "SharedConstants.h"
#include "day/day08.h"
#include <functional>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AoC22;
using AoC22::IO::DataInstance;

namespace TestLibrary
{
	TEST_CLASS(TestLibrary_Day_08)
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
			Days::Day08 day(input);

			auto resultEx = UnwrapResult<Days::DayIntegerResult>(
				[&day]() { return day.runFirst(true); 
			});

			Assert::AreEqual(21u, resultEx.first->Value, L"Example data has wrong result");

			auto result = UnwrapResult<Days::DayIntegerResult>(
				[&day]() { return day.runFirst(false);
			});

			Logger::WriteMessage(Shared::WideStr(resultEx.first->Value).c_str());
			Logger::WriteMessage(Shared::WideStr(result.first->Value).c_str());
		}

		TEST_METHOD(Second)
		{
			Days::Day08 day(input);

			auto resultEx = UnwrapResult<Days::DayIntegerResult>(
				[&day]() { return day.runSecond(true);
			});
			
			Assert::AreEqual(8u, resultEx.first->Value, L"Example data has wrong result");

			auto result = UnwrapResult<Days::DayIntegerResult>(
				[&day]() { return day.runSecond(false);
			});


			Logger::WriteMessage(Shared::WideStr(resultEx.first->Value).c_str());
			Logger::WriteMessage(Shared::WideStr(result.first->Value).c_str());
		}
	};
}
