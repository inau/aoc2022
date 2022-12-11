#include "CppUnitTest.h"
#include "SharedConstants.h"
#include "io/dataInstance.h"
//#include "io/reader.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestLibrary
{
	TEST_CLASS(TestLibrary_Day_00)
	{
	protected:
		void StreamTester(std::ifstream& strm, const std::string expectedLine, std::wstring message = L"")
		{
			if (strm)
			{
				std::string line;
				while (!strm.eof() && strm >> line)
				{
					Assert::IsFalse(line.empty());
					Assert::AreEqual(expectedLine, line);
				}
			}
			else Assert::Fail(message.c_str());
		}

	public:
		
		TEST_METHOD(DataInstance)
		{
			using AoC22::IO::DataInstance;

			std::wstring path = Shared::InputDataRoot;

			auto example = DataInstance::CreateDataInstance(path, 0, DataInstance::Type::EXAMPLE, 0); // 2
			StreamTester(example.getStream(), "example", L"example file failed");
			auto first = DataInstance::CreateDataInstance(path, 0, DataInstance::Type::INPUT, 0); // 10
			StreamTester(first.getStream(), "first", L"input file failed");

		}
	};
}
