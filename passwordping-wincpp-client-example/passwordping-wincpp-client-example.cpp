// passwordping-wincpp-client-example.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "passwordping-wincpp-client.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	DWORD dwResult = InitPasswordPing(L"<your api key here>", L"<your api secret here>");
	BOOL bResult = FALSE;

	dwResult = CheckPassword(L"123456", &bResult);

	if (dwResult == 0) {
		wcout << "Password: 123456, Result: " << (bResult ? "bad" : "good") << "\n";
	}
	else {
		wcout << "Error checking password: " << dwResult << "\n";
	}

	dwResult = CheckPassword(L"thisisnotabadpassword", &bResult);

	if (dwResult == 0) {
		wcout << "Password: thisisnotabadpassword, Result: " << (bResult ? "bad" : "good") << "\n";
	}
	else {
		wcout << "Error checking password: " << dwResult << "\n";
	}

	system("pause");

    return 0;
}

