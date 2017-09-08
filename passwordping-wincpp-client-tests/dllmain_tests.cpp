#include "stdafx.h"
#include "CppUnitTest.h"
#include <stdio.h>
#include <windows.h>
#include "webservice.cpp"
#include "dllmain.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace passwordpingwincppclienttests
{
	TEST_CLASS(dllmaintests)
	{
	public:

		TEST_METHOD(TestInitPasswordPing) 
		{
			DWORD dwResult = InitPasswordPing(L"<Your API Key Here>", L"<Your API Secret Here>");

			Assert::AreEqual(0ul, dwResult);
			Assert::AreEqual(L"NjA2MTZmMjM1NWE1NDkxMzk4YzU4YzE4NjA0NjkxYmY6ODdlMjk4MTk2ZTY2NDllOWE1Y2VlOWQwOTllZDIxYTA=", lpszAuthString);

		}

		TEST_METHOD(TestCheckPassword)
		{
			DWORD dwResult = InitPasswordPing(L"<Your API Key Here>", L"<Your API Secret Here>");
			
			Assert::AreEqual(0ul, dwResult);

			// first check a positive result
			BOOL bResult = FALSE;
			dwResult = CheckPassword(L"123456", &bResult);

			Assert::AreEqual(0ul, dwResult);
			Assert::AreEqual(TRUE, bResult);

			// now check a negative result
			bResult = FALSE;
			dwResult = CheckPassword(L"thispasswordisnotbad", &bResult);

			Assert::AreEqual(0ul, dwResult);
			Assert::AreEqual(FALSE, bResult);
		}

	};
}