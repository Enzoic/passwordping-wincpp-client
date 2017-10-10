#pragma once

#include <windows.h>

DWORD MakeWebServiceCall(LPWSTR page, LPWSTR params, LPWSTR authHeader, ULONG ulNetworkTimeout, 
	LPTSTR lpszProxyServer, int &statusCode);