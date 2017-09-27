#pragma once

#include <Windows.h>

#ifdef PASSWORDPINGWINCPPCLIENT_EXPORTS  
#define PASSWORDPING_API __declspec(dllexport)   
#else  
#define PASSWORDPING_API __declspec(dllimport)   
#endif  

/// <summary>
/// Initializes the library with your API key and secret.  Must be called first, prior to 
/// making any other calls.
/// </summary>
/// <param name="lpszAPIKey">Null terminated LPTSTR containing your PasswordPing API key</param>  
/// <param name="lpszSecret">Null terminated LPTSTR containing your PasswordPing API secret</param>  
/// <param name="ulNetworkTimeoutInMs">Unsigned long containing a timeout in milliseconds for API calls.  If 0 is provided, the default timeout (30 seconds) will be used.</param>
/// <returns>0 on success.  If non-zero, the return code is a standard Windows error code.</returns>  
PASSWORDPING_API DWORD __stdcall InitPasswordPing(LPTSTR lpszAPIKey, LPTSTR lpszSecret, ULONG ulNetworkTimeoutInMs);

/// <summary>
/// Checks a password against the PasswordPing API to determine if it is known to be compromised.
/// </summary>
/// <param name="lpszPassword">Null terminated LPTSTR containing the plaintext password to check.</param>  
/// <param name="pbResult">Pointer to a BOOL which will receive the result.  TRUE if password is compromised and FALSE if not.</param>  
/// <returns>
///   0 on success.  If non-zero, the return code is a standard Windows error code.  If called before InitPasswordPing, will return ERROR_NOT_READY.  
///   If an invalid API key or Secret were provided, returns ERROR_NOT_AUTHENTICATED.
///   If the request times out, ERROR_WINHTTP_TIMEOUT is returned.
/// </returns>  
PASSWORDPING_API DWORD __stdcall CheckPassword(LPTSTR lpszPassword, PBOOL pbResult);


// function types for LoadLibrary/GetProcAddress usage
typedef DWORD (__stdcall *f_InitPasswordPing)(LPTSTR lpszAPIKey, LPTSTR lpszSecret, ULONG ulNetworkTimeoutInMs);
typedef DWORD (__stdcall *f_CheckPassword)(LPTSTR lpszPassword, PBOOL pbResult);

