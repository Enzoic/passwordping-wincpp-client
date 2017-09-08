#pragma once

#include <Windows.h>

#ifdef __cplusplus
extern "C" {  // only need to export C interface if
			  // used by C++ source code
#endif

	extern __declspec(dllimport) DWORD __stdcall InitPasswordPing(LPTSTR lpszAPIKey, LPTSTR lpszSecret);
	extern __declspec(dllimport) DWORD __stdcall CheckPassword(LPTSTR lpszPassword, PBOOL bResult);


#ifdef __cplusplus
}
#endif
