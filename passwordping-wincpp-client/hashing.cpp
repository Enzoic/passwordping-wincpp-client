#include "stdafx.h"
#include "hashing.h"
#include <stdio.h>
#include <windows.h>
#include <wincrypt.h>

#pragma comment(lib, "crypt32.lib")

DWORD Hashing::CalcHashTypeUsingWinCrypt(ALG_ID iHashAlgType, DWORD cbHashLen, LPTSTR lpToHash, LPTSTR lpOutHash) {

	DWORD dwResult = 0;
	HCRYPTPROV hProv = 0;
	HCRYPTHASH hHash = 0;
	DWORD cbRead = 0;
	BYTE rgbHash[64];
	LPSTR lpToHashUTF8 = NULL;

	dwResult = ConvertWideToUTF8(lpToHash, lpToHashUTF8);

	if (dwResult == 0) {
		// convert to UTF8
		// Get handle to the crypto provider
		if (CryptAcquireContext(&hProv,
			NULL,
			MS_ENH_RSA_AES_PROV,
			PROV_RSA_AES,
			CRYPT_VERIFYCONTEXT))
		{
			if (CryptCreateHash(hProv, iHashAlgType, 0, 0, &hHash))
			{
				if (CryptHashData(hHash, (BYTE*)lpToHashUTF8, strlen(lpToHashUTF8), 0))
				{
					if (CryptGetHashParam(hHash, HP_HASHVAL, rgbHash, &cbHashLen, 0))
					{
						for (int i = 0; i < cbHashLen; i++) {
							wsprintf(lpOutHash + i * sizeof(TCHAR), L"%02x", rgbHash[i]);
						}
					}
					else
					{
						dwResult = GetLastError();
					}
				}
				else {
					dwResult = GetLastError();
				}

				CryptDestroyHash(hHash);
			}
			else {
				dwResult = GetLastError();
			}

			CryptReleaseContext(hProv, 0);
		}
		else {
			dwResult = GetLastError();
		}
	}
	else {
		HeapFree(GetProcessHeap(), HEAP_NO_SERIALIZE, lpToHashUTF8);
	}

	return dwResult;
}

DWORD Hashing::CalcMD5(LPTSTR lpToHash, LPTSTR lpOutHash)
{
	return CalcHashTypeUsingWinCrypt(CALG_MD5, 16, lpToHash, lpOutHash);
}

DWORD Hashing::CalcSHA1(LPTSTR lpToHash, LPTSTR lpOutHash)
{
	return CalcHashTypeUsingWinCrypt(CALG_SHA1, 20, lpToHash, lpOutHash);
}

DWORD Hashing::CalcSHA256(LPTSTR lpToHash, LPTSTR lpOutHash)
{
	return CalcHashTypeUsingWinCrypt(CALG_SHA_256, 64, lpToHash, lpOutHash);
}

DWORD Hashing::Base64Encode(LPTSTR lpToEncode, LPTSTR& lpEncoded)
{
	DWORD cbEncodedLen = 0;
	DWORD dwResult = 0;
	LPSTR lpToEncodeUTF8 = NULL;

	dwResult = ConvertWideToUTF8(lpToEncode, lpToEncodeUTF8);

	if (dwResult == 0) {
		// get length
		if (CryptBinaryToString(reinterpret_cast<const BYTE*>(lpToEncodeUTF8), strlen(lpToEncodeUTF8), CRYPT_STRING_BASE64 | CRYPT_STRING_NOCRLF, nullptr, &cbEncodedLen)) {
			lpEncoded = static_cast<LPTSTR>(HeapAlloc(GetProcessHeap(), HEAP_NO_SERIALIZE, cbEncodedLen * sizeof(TCHAR)));

			if (lpEncoded) {
				if (!CryptBinaryToString(reinterpret_cast<const BYTE*>(lpToEncodeUTF8), strlen(lpToEncodeUTF8), CRYPT_STRING_BASE64 | CRYPT_STRING_NOCRLF, lpEncoded, &cbEncodedLen)) {
					dwResult = GetLastError();
				}
			}
			else {
				dwResult = GetLastError();
			}
		}
		else {
			dwResult = GetLastError();
		}

		HeapFree(GetProcessHeap(), HEAP_NO_SERIALIZE, lpToEncodeUTF8);
	}
	else {
		dwResult = GetLastError();
	}

	return dwResult;
}

DWORD Hashing::ConvertWideToUTF8(LPTSTR lpWide, LPSTR& lpUTF8) {
	DWORD dwResult = 0;

	// first convert lpToEncode to UTF8 - get length with first call
	int cbToEncodeUTF8 = WideCharToMultiByte(CP_UTF8, 0, lpWide, wcslen(lpWide), NULL, 0, NULL, NULL);

	if (cbToEncodeUTF8 != 0) {
		// allocate buffer for UTF8
		lpUTF8 = static_cast<LPSTR>(HeapAlloc(GetProcessHeap(), HEAP_NO_SERIALIZE, cbToEncodeUTF8 + 1));

		if (lpUTF8) {
			memset(lpUTF8, 0, cbToEncodeUTF8 + 1);

			if (WideCharToMultiByte(CP_UTF8, 0, lpWide, wcslen(lpWide), lpUTF8, cbToEncodeUTF8, NULL, NULL) == 0) {
				// free the buffer before returning with error
				HeapFree(GetProcessHeap(), HEAP_NO_SERIALIZE, lpUTF8);

				dwResult = GetLastError();
			}
		}
		else {
			dwResult = GetLastError();
		}
	}
	else {
		dwResult = GetLastError();
	}

	return dwResult;
}
