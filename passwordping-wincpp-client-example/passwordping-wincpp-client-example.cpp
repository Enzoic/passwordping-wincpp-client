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
// first initialize the library with your API key and secret.  This should always be the first call
// made after loading the library.
DWORD dwResult = InitPasswordPing(L"YOUR_API_KEY", L"YOUR_API_SECRET");
BOOL bResult = FALSE;

// Call CheckPassword and check a password known to be compromised.
dwResult = CheckPassword(L"123456", &bResult);

// If successful, bResult wil contain the compromise status (true for compromised and false for not)
if (dwResult == ERROR_SUCCESS) {
	wcout << "Password: 123456, Result: " << (bResult ? "bad" : "good") << "\n";
}
else {
	wcout << "Error checking password: " << dwResult << "\n";
}

// Now call CheckPassword with a password known to not be compromised. 
dwResult = CheckPassword(L"thisisnotabadpassword", &bResult);

// If successful, bResult wil contain the compromise status (true for compromised and false for not)
if (dwResult == ERROR_SUCCESS) {
	wcout << "Password: thisisnotabadpassword, Result: " << (bResult ? "bad" : "good") << "\n";
}
else {
	wcout << "Error checking password: " << dwResult << "\n";
}

	system("pause");

    return 0;
}

