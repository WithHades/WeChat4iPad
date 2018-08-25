#include "stdafx.h"
#include <time.h>
#include "fun.h"



string Hex2bin(CStringA strHex)
{
	string strRet;
	DWORD dwCur = 0;

	strHex.Remove(' ');
	strHex.MakeLower();

	strRet.resize(strHex.GetLength() / 2);

	while (strHex.GetLength() >= 2)
	{		
		CStringA strTemp = strHex.Left(2);

		strHex = strHex.Mid(2);

		DWORD dwHex = 0;

		unsigned char c = strTemp[0];
		if (c >= '0' && c <= '9')
		{
			dwHex += (c - '0') * 16;
		}
		else if (c >= 'a' && c <= 'f')
		{
			dwHex += (c - 'a' + 10) * 16;
		}
		else
		{
			continue;
		}

		c = strTemp[1];
		if (c >= '0' && c <= '9')
		{
			dwHex += (c - '0');
		}
		else if (c >= 'a' && c <= 'f')
		{
			dwHex += (c - 'a' + 10);
		}
		else
		{
			continue;
		}

		strRet[dwCur++] = dwHex;
	}

	return strRet;
}

std::string Bin2Hex(string &strBin)
{
	string str;
	char szTemp[10] = { 0 };

	for (int i=0;i<strBin.size();i++)
	{
		sprintf(szTemp,"%02x ",(unsigned char)strBin[i]);
		str = str + szTemp;
	}

	return str;
}

//------------------------------------------------------------------------ 
std::string string_To_UTF8(const std::string & str)
{
	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

	wchar_t * pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴 
	ZeroMemory(pwBuf, nwLen * 2 + 2);

	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	char * pBuf = new char[nLen + 1];
	ZeroMemory(pBuf, nLen + 1);

	::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string retStr(pBuf);

	delete[]pwBuf;
	delete[]pBuf;

	pwBuf = NULL;
	pBuf = NULL;

	return retStr;
}
//----------------------------------------------------------------------- 
std::string UTF8_To_string(const std::string & str)
{
	int nwLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);

	wchar_t * pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴 
	memset(pwBuf, 0, nwLen * 2 + 2);

	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), pwBuf, nwLen);

	int nLen = WideCharToMultiByte(CP_ACP, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	char * pBuf = new char[nLen + 1];
	memset(pBuf, 0, nLen + 1);

	WideCharToMultiByte(CP_ACP, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string retStr = pBuf;

	delete[]pBuf;
	delete[]pwBuf;

	pBuf = NULL;
	pwBuf = NULL;

	return retStr;
}
////////////////////////////////////////////////////////////////////////// 


////////////////////////////////////////////////////////////////////////// 
//  [8/19/2009 Leezhm] 
//  translate ascii characters to utf-8 characters


string Dword2String(DWORD dw)
{
	DWORD dwData = dw;
	DWORD dwData2 = 0x80 * 0x80 * 0x80 * 0x80;
	int nLen = 4;
	byte hex[5] = { 0 };
	DWORD dwOutLen = 0;

	while (nLen > 0)
	{
		if (dwData > dwData2)
		{
			hex[nLen] = dwData / dwData2;
			dwData = dwData % dwData2;
			dwOutLen++;
		}

		dwData2 /= 0x80;
		nLen--;
	}

	hex[0] = dwData;
	dwOutLen++;

	for (int i = 0; i < (int)(dwOutLen - 1); i++)
	{
		hex[i] += 0x80;
	}

	return string((const char *)hex, dwOutLen);
}

DWORD String2Dword(string str, DWORD &dwOutLen)
{
	DWORD dwLen = str.size();

	if (!dwLen)	return 0;


	DWORD dwRet = 0;
	DWORD dwTemp = 1;
	int nLen = 0;
	while (nLen < 5 && nLen<dwLen)
	{
		unsigned char c = (unsigned char)str[nLen];

		if (!(c >> 7))
		{
			dwRet += c * dwTemp;
			nLen++;
			break;
		}
		else
		{
			dwRet += (c & 0x7f) * dwTemp;
			dwTemp *= 0x80;
			nLen++;
		}
	}

	dwOutLen = nLen;

	return dwRet;
}

static void MessageBoxThread(LPCTSTR szMsg)
{
	MessageBox(NULL, szMsg,NULL,NULL);
}
void ForceQuit(CString str)
{
	CloseHandle(CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MessageBoxThread, str.GetBuffer(), NULL, NULL));
	Sleep(3*1000);
	TerminateProcess(GetCurrentProcess(), 0);
}

void LOG(const char *szLog, ...)
{
	va_list va;
	va_start(va, szLog);
	char buffer[65535] = {0};
	vsprintf(buffer, szLog, va);
	va_end(va);

	time_t rawtime;
	time(&rawtime);
	char* szTime = ctime(&rawtime);
	*(szTime + strlen(szTime) - 1) = 0;
	char Buff[65535] = { 0 };
	sprintf(Buff, "[%s] %s \r\n", szTime, buffer);

	//象征性的Log:若需要log辅助debug,请使用xLog
	printf(Buff);
}

