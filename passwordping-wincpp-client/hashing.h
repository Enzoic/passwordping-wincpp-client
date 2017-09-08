#pragma once
#include <Wincrypt.h>

class Hashing {
public:
	static DWORD Base64Encode(LPTSTR lpToEncode, LPTSTR& lpEncoded);
	static DWORD CalcMD5(LPTSTR lpToHash, LPTSTR lpOutHash);
	static DWORD CalcSHA1(LPTSTR lpToHash, LPTSTR lpOutHash);
	static DWORD CalcSHA256(LPTSTR lpToHash, LPTSTR lpOutHash);
private:
	Hashing() {}
	static DWORD CalcHashTypeUsingWinCrypt(ALG_ID iHashAlgType, DWORD cbHashLen, LPTSTR lpToHash, LPTSTR lpOutHash);
	static DWORD ConvertWideToUTF8(LPTSTR lpWide, LPSTR& lpUTF8);
};


