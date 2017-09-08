#pragma once

#include <Windows.h>

#ifdef __cplusplus
extern "C" {  // only need to export C interface if
			  // used by C++ source code
#endif


	/// <summary>
	/// Initializes the library with your API key and secret.  Must be called first, prior to 
	/// making any other calls.
	/// </summary>
	/// <param name="lpszAPIKey">Null terminated LPTSTR containing your PasswordPing API key</param>  
	/// <param name="lpszSecret">Null terminated LPTSTR containing your PasswordPing API secret</param>  
	/// <returns>0 on success.  If non-zero, the return code is a standard Windows error code.</returns>  
	extern __declspec(dllimport) DWORD __stdcall InitPasswordPing(LPTSTR lpszAPIKey, LPTSTR lpszSecret);

	/// <summary>
	/// Checks a password against the PasswordPing API to determine if it is known to be compromised.
	/// </summary>
	/// <param name="lpszPassword">Null terminated LPTSTR containing the plaintext password to check.</param>  
	/// <param name="pbResult">Pointer to a BOOL which will receive the result.  TRUE if password is compromised and FALSE if not.</param>  
	/// <returns>0 on success.  If non-zero, the return code is a standard Windows error code.  If called before InitPasswordPing, will return ERROR_NOT_READY.</returns>  
	extern __declspec(dllimport) DWORD __stdcall CheckPassword(LPTSTR lpszPassword, PBOOL pbResult);


#ifdef __cplusplus
}
#endif
