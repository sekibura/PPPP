#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab2/function.h"
#include <string>

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Lab2Tests
{
	TEST_CLASS(Lab2Tests)
	{
	public:
		
		TEST_METHOD(start_func)
		{
			string result = Tst::start_func(0, 0, 0, 0, 0, 0);
			Assert::IsTrue(result == "5",L"Assert 0,0,0,0,0,0 ");
		}

		TEST_METHOD2(start_func)
		{
			string result = Tst::start_func(0, 0, 0, 0, 0, 0);
			Assert::IsTrue(result == "5", L"Assert 0,0,0,0,0,0 ");
		}
	};
}
