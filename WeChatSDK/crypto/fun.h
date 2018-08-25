#pragma once
#include <atlstr.h>
#include <string>



using namespace std;

//protobuf与string转换
string Hex2bin(CStringA strHex);
string Bin2Hex(string &strBin);

//Utf8编码解码
std::string string_To_UTF8(const std::string & str);
std::string UTF8_To_string(const std::string & str);

//变长整数编码解码
string Dword2String(DWORD dw);
DWORD String2Dword(string str,DWORD &dwOutLen);

//异常;强退



void LOG(const char *szLog, ...);






