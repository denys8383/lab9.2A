#include "pch.h"
#include "CppUnitTest.h"
#include "../Project9.2A/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest92A
{
	TEST_CLASS(UnitTest92A)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Specialty specialty = MATH_ECONOMICS;
			const char* str = specialtiesToString(specialty);
			Assert::AreEqual("Mathematics and economics", str);
		}
	};
}
