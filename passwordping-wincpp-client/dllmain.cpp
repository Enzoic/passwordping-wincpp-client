// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "hashing.h"
#include "webservice.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

LPTSTR lpszAuthString = NULL;

extern "C" __declspec(dllexport) DWORD __stdcall
InitPasswordPing(LPTSTR lpszAPIKey, LPTSTR lpszSecret) {
	TCHAR szAuthStringTemp[1024];
	memset(szAuthStringTemp, 0, sizeof(szAuthStringTemp));

	wsprintf(szAuthStringTemp, L"%s:%s", lpszAPIKey, lpszSecret);

	Hashing::Base64Encode(szAuthStringTemp, lpszAuthString);

	return 0;
}

extern "C" __declspec(dllexport) DWORD __stdcall
CheckPassword(LPTSTR lpszPassword, PBOOL pbResult) {

	if (lpszAuthString == NULL) {
		// not initialized
		return ERROR_NOT_READY;
	}

	TCHAR md5[33];
	TCHAR sha1[41];
	TCHAR sha256[65];
	DWORD dwResult = 0;

	memset(md5, 0, sizeof(md5));
	memset(sha1, 0, sizeof(sha1));
	memset(sha256, 0, sizeof(sha256));

	*pbResult = FALSE;

	dwResult = Hashing::CalcMD5(lpszPassword, md5);

	if (dwResult != 0) {
		return dwResult;
	}
	
	dwResult = Hashing::CalcSHA1(lpszPassword, sha1);

	if (dwResult != 0) {
		return dwResult;
	}

	dwResult = Hashing::CalcSHA256(lpszPassword, sha256);

	if (dwResult != 0) {
		return dwResult;
	}

	TCHAR szParams[1024];
	wsprintf(szParams, L"md5=%s&sha1=%s&sha256=%s", md5, sha1, sha256);

	int statusCode = 0;
	dwResult = MakeWebServiceCall(L"passwords", szParams,
		lpszAuthString, 
		statusCode);

	if (dwResult != 0) {
		return dwResult;
	}

	if (statusCode == 200) {
		*pbResult = TRUE;
	}

	SecureZeroMemory(md5, sizeof(md5));
	SecureZeroMemory(sha1, sizeof(sha1));
	SecureZeroMemory(sha256, sizeof(sha256));

	return 0;
}


