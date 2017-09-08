#include "stdafx.h"
#include "CppUnitTest.h"
#include <stdio.h>
#include <windows.h>
#include "hashing.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace passwordpingwincppclienttests
{		
	TEST_CLASS(hashingtests)
	{
	public:
		
		TEST_METHOD(TestCalcMD5)
		{			
			TCHAR resultStr[33];
			memset(resultStr, 0, 33);

			DWORD dwResult = Hashing::CalcMD5(L"123456", resultStr);

			Assert::AreEqual(0ul, dwResult);
			Assert::AreEqual(L"e10adc3949ba59abbe56e057f20f883e", resultStr);
			Assert::AreEqual(static_cast<size_t>(32), wcslen(resultStr));
		}

		TEST_METHOD(TestCalcSHA1) 
		{
			TCHAR resultStr[41];
			memset(resultStr, 0, 41);

			DWORD dwResult = Hashing::CalcSHA1(L"123456", resultStr);

			Assert::AreEqual(0ul, dwResult);
			Assert::AreEqual(L"7c4a8d09ca3762af61e59520943dc26494f8941b", resultStr);
			Assert::AreEqual(static_cast<size_t>(40), wcslen(resultStr));
		}

		TEST_METHOD(TestCalcSHA256)
		{
			TCHAR resultStr[65];
			memset(resultStr, 0, 65);

			DWORD dwResult = Hashing::CalcSHA256(L"123456", resultStr);

			Assert::AreEqual(0ul, dwResult);
			Assert::AreEqual(L"8d969eef6ecad3c29a3a629280e686cf0c3f5d5a86aff3ca12020c923adc6c92", resultStr);
			Assert::AreEqual(static_cast<size_t>(64), wcslen(resultStr));
		}

		TEST_METHOD(TestBase64Encode) 
		{
			LPTSTR lpEncoded = NULL;

			DWORD dwResult = Hashing::Base64Encode(L"123456", lpEncoded);

			Assert::AreEqual(L"MTIzNDU2", lpEncoded);

			HeapFree(GetProcessHeap(), HEAP_NO_SERIALIZE, lpEncoded);
		}

	};
}