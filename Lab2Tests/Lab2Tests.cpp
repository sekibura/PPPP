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

			result = Tst::start_func(1, 0, 0, 1, 1, 0);
			Assert::IsTrue(result==("2 " + to_string((float)1) + ' ' + to_string((float)0)), L"Assert 1, 0, 0, 1, 1, 0");
			
			result = Tst::start_func(1, 0, 0, 1, 0, 1);
			Assert::IsTrue(result==("2 " + to_string((float)0) + ' ' + to_string((float)1)), L"Assert 1, 0, 0, 1, 0, 1");

			result = Tst::start_func(0, 0, 0, 1, 1, 0);
			Assert::IsTrue(result=="0", L"Assert 0, 0, 0, 1, 1, 0");

			result = Tst::start_func(0, 0, 0, 1, 0, 0);
			Assert::IsTrue(result=="4 "+to_string((float)0), L"Assert 0, 0, 0, 1, 0, 0");

			result = Tst::start_func(0, 1, 0, 0, 1, 0);
			Assert::IsTrue(result == "4 " + to_string((float)1), L"Assert 0, 1, 0, 0, 1, 0");

			result = Tst::start_func(0, 0, 1, 0, 0, 1);
			Assert::IsTrue(result == "3 " + to_string((float)1), L"Assert 0, 0, 1, 0, 0, 1");

			result = Tst::start_func(1, 0, 0, 0, 1, 0);
			Assert::IsTrue(result == "3 " + to_string((float)1), L"Assert 1, 0, 0, 0, 1, 0");

			result = Tst::start_func(0, 1, 0, 1, 1, 1);
			Assert::IsTrue(result == "4 " + to_string((float)1), L"Assert 0, 1, 0, 1, 1, 1  a == 0 && c == 0");

			result = Tst::start_func(1, 0, 1, 0, 1, 1);
			Assert::IsTrue(result == "3 " + to_string((float)1), L"Assert 1, 0, 1, 0, 1, 1  b == 0 && d == 0");

			result = Tst::start_func(0, 0, 1, 1, 0, 1);
			Assert::IsTrue(result == "1 " + to_string((float)(-1))+' '+to_string((float)1), L"Assert 1, 0, 1, 0, 1, 1  b == 0 && e == 0");

			result = Tst::start_func(1, 1, 0, 0, 1, 0);
			Assert::IsTrue(result == "1 " + to_string((float)(-1))+' '+to_string((float)1), L"Assert 1, 1, 0, 0, 1, 0  d == 0 && f == 0");

			result = Tst::start_func(0, 1, 1, 1, 0, 0);
			Assert::IsTrue(result == "1 " + to_string((float)(-1))+' '+to_string((float)0), L"Assert 0, 1, 1, 1, 0, 0 a == 0 && e == 0");

			result = Tst::start_func(1, 1, 0, 1, 0, 0);
			Assert::IsTrue(result == "1 " + to_string((float)(-1)) + ' ' + to_string((float)0), L"Assert 1, 1, 0, 1, 0, 0 c == 0 && f == 0");

			result = Tst::start_func(1, 1, 1, 1, 0, 0);
			Assert::IsTrue(result == "1 " + to_string((float)(-1)) + ' ' + to_string((float)0), L"Assert 1, 1, 1, 1, 0, 0 (a / b == c / d)");


			result = Tst::start_func(1, 1, 1, 1, 1, 0);
			Assert::IsTrue(result == "0", L"Assert 1, 1, 1, 1, 1, 0 (a*d - c * b == 0) && (e*d - b * f != 0)");

			result = Tst::start_func(1, 1, 1, 1, 0, 1);
			Assert::IsTrue(result == "0", L"Assert 1, 1, 1, 1, 0, 1 (a*d - c * b == 0) &&  (a*f - c * e != 0)");
		}

	
	};
}
