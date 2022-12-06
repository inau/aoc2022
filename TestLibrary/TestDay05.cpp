#include "CppUnitTest.h"
#include "SharedConstants.h"
#include "day/day05.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AoC22;
using AoC22::IO::DataInstance;

namespace TestLibrary
{
	TEST_CLASS(TestLibrary_Day_05)
	{
	protected:
		AoC22::IO::InputDataReader& input = Shared::InputInstance();

	public:
		
		TEST_METHOD(First)
		{
			Days::Day05 day(input);

			auto baseresultEx = day.runFirst(true);
			Days::DayStringResult* resultEx
				= dynamic_cast<Days::DayStringResult*>(baseresultEx.get());
			auto baseresult = day.runFirst(false);
			Days::DayStringResult* result
				= dynamic_cast<Days::DayStringResult*>(baseresult.get());

		//	Logger::WriteMessage(Shared::GetName(1, Shared::FirstAssignmentStr).c_str());
			Logger::WriteMessage(resultEx->Value.c_str());
			Logger::WriteMessage(result->Value.c_str());
		}

		TEST_METHOD(Second)
		{
			Days::Day05 day(input);

			auto baseresultEx = day.runSecond(true);
			Days::DayStringResult* resultEx
				= dynamic_cast<Days::DayStringResult*>(baseresultEx.get());
			auto baseresult = day.runSecond(false);
			Days::DayStringResult* result
				= dynamic_cast<Days::DayStringResult*>(baseresult.get());

		//	Logger::WriteMessage(Shared::GetName(1, Shared::SecondAssignmentStr).c_str());
			Logger::WriteMessage((resultEx->Value).c_str());
			Logger::WriteMessage((result->Value).c_str());
		}
	};
}
