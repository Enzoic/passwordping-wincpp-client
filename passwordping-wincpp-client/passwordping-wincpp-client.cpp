// passwordping-wincpp-client.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "passwordping-wincpp-client.h"
#include "hashing.h"
#include "webservice.h"

LPTSTR lpszAuthString = NULL;
ULONG ulNetworkTimeout = 0;

DWORD __stdcall InitPasswordPing(LPTSTR lpszAPIKey, LPTSTR lpszSecret, ULONG ulNetworkTimeoutInMs) {
	TCHAR szAuthStringTemp[1024];
	memset(szAuthStringTemp, 0, sizeof(szAuthStringTemp));

	wsprintf(szAuthStringTemp, L"%s:%s", lpszAPIKey, lpszSecret);

	Hashing::Base64Encode(szAuthStringTemp, lpszAuthString);

	ulNetworkTimeout = ulNetworkTimeoutInMs;

	return 0;
}

DWORD __stdcall CheckPassword(LPTSTR lpszPassword, PBOOL pbResult) {

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

	if (dwResult == ERROR_SUCCESS) {

		dwResult = Hashing::CalcSHA1(lpszPassword, sha1);

		if (dwResult == ERROR_SUCCESS) {

			dwResult = Hashing::CalcSHA256(lpszPassword, sha256);

			if (dwResult == ERROR_SUCCESS) {

				TCHAR szParams[1024];
				wsprintf(szParams, L"md5=%s&sha1=%s&sha256=%s", md5, sha1, sha256);

				int statusCode = 0;
				dwResult = MakeWebServiceCall(L"passwords", szParams,
					lpszAuthString, ulNetworkTimeout,
					statusCode);

				if (dwResult == ERROR_SUCCESS) {
					if (statusCode == 200) {
						*pbResult = TRUE;
					}
					else if (statusCode == 404) {
						*pbResult = FALSE;
					}
					else if (statusCode == 401) {
						dwResult = ERROR_NOT_AUTHENTICATED;
					}
					else {
						dwResult = ERROR_UNEXP_NET_ERR;
					}
				}
			}
		}
	}

	SecureZeroMemory(md5, sizeof(md5));
	SecureZeroMemory(sha1, sizeof(sha1));
	SecureZeroMemory(sha256, sizeof(sha256));

	return dwResult;
}

