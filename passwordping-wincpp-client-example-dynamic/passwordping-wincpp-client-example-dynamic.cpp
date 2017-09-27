// 
// This project shows how to load the PasswordPing DLL dynamically at runtime using LoadLibrary/GetProcAddress
//

#include "stdafx.h"
#include "passwordping-wincpp-client.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

// TODO: add your API key and secret here
#define API_KEY L"YOUR_API_KEY"
#define API_SECRET L"YOUR_API_SECRET"

int main()
{
	// load the DLL dynamically
	HINSTANCE hPasswordPingLib = LoadLibrary(L"passwordping-wincpp-client.dll");

	if (!hPasswordPingLib) {
		std::cout << "could not load the PasswordPing DLL" << std::endl;
		return EXIT_FAILURE;
	}

	// load the functions
	f_InitPasswordPing InitPasswordPing = (f_InitPasswordPing)GetProcAddress(hPasswordPingLib, "InitPasswordPing");
	f_CheckPassword CheckPassword = (f_CheckPassword)GetProcAddress(hPasswordPingLib, "CheckPassword");
	if (!InitPasswordPing || !CheckPassword) {
		std::cout << "could not locate the PasswordPing functions" << std::endl;
		return EXIT_FAILURE;
	}

	// first initialize the library with your API key and secret.  This should always be the first call
	// made after loading the library.
	DWORD dwResult = InitPasswordPing(API_KEY, API_SECRET, 0);
	BOOL bResult = FALSE;

	// Call CheckPassword and check a password known to be compromised.
	dwResult = CheckPassword(L"123456", &bResult);

	wcout << "Password: 123456, Result: ";

	// If successful, bResult wil contain the compromise status (true for compromised and false for not)
	if (dwResult == ERROR_SUCCESS) {
		wcout << (bResult ? "bad" : "good") << "\n";
	}
	else if (dwResult == ERROR_NOT_AUTHENTICATED) {
		wcout << "Error - invalid API key provided" << "\n";
	}
	else {
		wcout << "Error checking password: " << dwResult << "\n";
	}

	// Now call CheckPassword with a password known to not be compromised. 
	dwResult = CheckPassword(L"thisisnotabadpassword", &bResult);

	wcout << "Password: thisisnotabadpassword, Result: ";

	// If successful, bResult wil contain the compromise status (true for compromised and false for not)
	if (dwResult == ERROR_SUCCESS) {
		wcout << (bResult ? "bad" : "good") << "\n";
	}
	else if (dwResult == ERROR_NOT_AUTHENTICATED) {
		wcout << "Error - invalid API key provided" << "\n";
	}
	else {
		wcout << "Error checking password: " << dwResult << "\n";
	}

	system("pause");

	return EXIT_SUCCESS;
}

