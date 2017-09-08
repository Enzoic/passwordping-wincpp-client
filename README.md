# PasswordPing Client DLL for Windows

## TOC

This README covers the following topics:

- [Installation](#installation)
- [API Overview](#api-overview)
- [InitPasswordPing Function](#initpasswordping-function)
- [CheckPassword Function](#checkpassword-function)
- [License](#license)

## Installation

Clone the source from Github, open the solution in Visual Studio and compile the DLL.  

## API Overview

Here's the API in a nutshell.  This is from the passwordping-wincpp-client-example application.

```cpp
// first initialize the library with your API key and secret.  This should always be the first call
// made after loading the library.
DWORD dwResult = InitPasswordPing(L"<your api key here>", L"<your api secret here>");
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
```

More information in reference format can be found below.

## InitPasswordPing

Must be the first call made after loading the library, prior to calling CheckPassword. Takes null-terminated strings containing the API key and secret you were issued on PasswordPing signup.  Returns a standard Windows error code response.

```cpp
DWORD dwResult = InitPasswordPing(L"YOUR_API_KEY", L"YOUR_API_SECRET");
```

## CheckPassword

Checks a password for compromised status against the PasswordPing Passwords API.  The first parameter is a null-terminated string containing the password to check.  The second parameter is a pointer to a boolean which will receive the compromised status of the password.  Returns a standard Windows error code response.

```cpp
BOOL bResult;
DWORD dwResult = CheckPassword(L"password", &bResult);
```

## License

This code is free to use under the terms of the MIT license.
