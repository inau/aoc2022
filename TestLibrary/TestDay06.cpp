#include "CppUnitTest.h"
#include "SharedConstants.h"
#include "day/day06.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AoC22;
using AoC22::IO::DataInstance;

namespace TestLibrary
{
	TEST_CLASS(TestLibrary_Day_06)
	{
	protected:
		AoC22::IO::InputDataReader& input = Shared::InputInstance();

	public:
		
		TEST_METHOD(First)
		{
			Days::Day06 day(input);

			auto baseresultEx = day.runFirst(true);
			Days::DayIntegerResult* resultEx
				= dynamic_cast<Days::DayIntegerResult*>(baseresultEx.get());
			auto baseresult = day.runFirst(false);
			Days::DayIntegerResult* result
				= dynamic_cast<Days::DayIntegerResult*>(baseresult.get());

		//	Logger::WriteMessage(Shared::GetName(1, Shared::FirstAssignmentStr).c_str());
			Logger::WriteMessage(Shared::WideStr(resultEx->Value).c_str());
			Logger::WriteMessage(Shared::WideStr(result->Value).c_str());
		}

		TEST_METHOD(Second)
		{
			Days::Day06 day(input);

			auto baseresultEx = day.runSecond(true);
			Days::DayIntegerResult* resultEx
				= dynamic_cast<Days::DayIntegerResult*>(baseresultEx.get());
			auto baseresult = day.runSecond(false);
			Days::DayIntegerResult* result
				= dynamic_cast<Days::DayIntegerResult*>(baseresult.get());

			Logger::WriteMessage(Shared::WideStr(resultEx->Value).c_str());
			Logger::WriteMessage(Shared::WideStr(result->Value).c_str());
		}
	};
}
