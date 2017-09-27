#include "stdafx.h"
#include "webservice.h"
#include <wininet.h>
#include <stdlib.h>

#pragma comment(lib, "wininet.lib")

DWORD MakeWebServiceCall(LPWSTR page, LPWSTR params, LPWSTR authHeader, ULONG ulNetworkTimeout, int &statusCode) {
	char szData[1024];
	DWORD dwResult = 0;

	// initialize WinInet
	HINTERNET hInternet = ::InternetOpen(TEXT("PasswordPingCPPClient"), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if (hInternet != NULL)
	{
		if (ulNetworkTimeout > 0) {
			InternetSetOption(hInternet, INTERNET_OPTION_CONNECT_TIMEOUT, &ulNetworkTimeout, sizeof(ulNetworkTimeout));
			InternetSetOption(hInternet, INTERNET_OPTION_CONTROL_RECEIVE_TIMEOUT, &ulNetworkTimeout, sizeof(ulNetworkTimeout));
			InternetSetOption(hInternet, INTERNET_OPTION_CONTROL_SEND_TIMEOUT, &ulNetworkTimeout, sizeof(ulNetworkTimeout));
			InternetSetOption(hInternet, INTERNET_OPTION_RECEIVE_TIMEOUT, &ulNetworkTimeout, sizeof(ulNetworkTimeout));
			InternetSetOption(hInternet, INTERNET_OPTION_SEND_TIMEOUT, &ulNetworkTimeout, sizeof(ulNetworkTimeout));
		}

		// open HTTP session
		HINTERNET hConnect = ::InternetConnect(hInternet, L"api.passwordping.com", INTERNET_DEFAULT_HTTPS_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, INTERNET_FLAG_SECURE, 1);

		if (hConnect != NULL)
		{
			WCHAR szHeaders[1024];
			WCHAR szRequest[1024];
			memset(szHeaders, 0, sizeof(szHeaders));
			memset(szRequest, 0, sizeof(szRequest));

			wsprintf(szHeaders, L"authorization: basic %s", authHeader);

			if (params == NULL || params[0] == '\0')
			{
				wsprintf(szRequest, L"%s", page);
			}
			else
			{
				wsprintf(szRequest, L"%s?%s", page, params);
			}

			//wstring request = _page +
			//	(_params.empty() ? L"" : (L"?" + _params));

			// open request
			HINTERNET hRequest = ::HttpOpenRequest(hConnect, L"GET", szRequest, NULL, NULL, 0, INTERNET_FLAG_KEEP_CONNECTION | INTERNET_FLAG_SECURE | INTERNET_FLAG_NO_CACHE_WRITE, 1);
			if (hRequest != NULL)
			{
				// send request
				BOOL isSend = ::HttpSendRequest(hRequest, szHeaders, 0, NULL, 0);

				if (isSend)
				{
					WCHAR responseText[256]; // change to wchar_t for unicode
					DWORD responseTextSize = sizeof(responseText);

					BOOL isInfo = HttpQueryInfo(hRequest,
						HTTP_QUERY_STATUS_CODE,
						&responseText,
						&responseTextSize,
						NULL);

					if (isInfo) {
						statusCode = _wtoi(responseText);

						if (statusCode == 200) {

							for (;;)
							{
								// reading data
								DWORD dwByteRead;
								BOOL isRead = ::InternetReadFile(hRequest, szData, sizeof(szData) - 1, &dwByteRead);

								// break cycle if error or end
								if (isRead == FALSE || dwByteRead == 0)
									break;

								// saving result
								szData[dwByteRead] = 0;
							}
						}
					}
					else {
						dwResult = GetLastError();
					}
				}
				else {
					dwResult = GetLastError();
				}

				// close request
				::InternetCloseHandle(hRequest);
			}
			else {
				dwResult = GetLastError();
			}

			// close session
			::InternetCloseHandle(hConnect);
		}
		else {
			dwResult = GetLastError();
		}

		// close WinInet
		::InternetCloseHandle(hInternet);
	}
	else {
		dwResult = GetLastError();
	}
	
	return dwResult;
}
