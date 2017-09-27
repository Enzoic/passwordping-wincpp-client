#include "stdafx.h"
#include "CppUnitTest.h"
#include <stdio.h>
#include <windows.h>
#include "webservice.cpp"
#include "passwordping-wincpp-client.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// TODO: add your API key and secret here
#define API_KEY L"YOUR_API_KEY"
#define API_SECRET L"YOUR_API_SECRET"

namespace passwordpingwincppclienttests
{
	TEST_CLASS(passwordpingwincppclienttests)
	{
	public:

		TEST_METHOD(TestInitPasswordPing) 
		{
			LONG dwResult = InitPasswordPing(API_KEY, API_SECRET, 0);

			Assert::AreEqual(ERROR_SUCCESS, dwResult);
		}

		TEST_METHOD(TestCheckPassword)
		{
			BOOL bResult = FALSE;

			LONG dwResult = CheckPassword(L"123456", &bResult);

			Assert::AreEqual(ERROR_NOT_READY, dwResult);

			dwResult = InitPasswordPing(L"junk", L"wrong", 1000);
			dwResult = CheckPassword(L"1234567", &bResult);

			Assert::AreEqual(ERROR_NOT_AUTHENTICATED, dwResult);

			dwResult = InitPasswordPing(API_KEY, API_SECRET, 0);
			
			Assert::AreEqual(ERROR_SUCCESS, dwResult);

			// first check a positive result
			dwResult = CheckPassword(L"123456", &bResult);

			Assert::AreEqual(ERROR_SUCCESS, dwResult);
			Assert::AreEqual(TRUE, bResult);

			// now check a negative result
			bResult = FALSE;
			dwResult = CheckPassword(L"thispasswordisnotbad", &bResult);

			Assert::AreEqual(ERROR_SUCCESS, dwResult);
			Assert::AreEqual(FALSE, bResult);
		}

	};
}