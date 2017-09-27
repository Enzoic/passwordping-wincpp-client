#pragma once

#include <windows.h>

DWORD MakeWebServiceCall(LPWSTR page, LPWSTR params, LPWSTR authHeader, ULONG ulNetworkTimeout, int &statusCode);