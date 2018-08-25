#include "stdafx.h"
#include "MakeHeader.h"
#include "fun.h"
#include "WxUser.h"
#include "TT.h"





std::string BaseHeader::MakeHeader(void*handle, int cgiType, int nLenProtobuf, int nLenCompressed)
{
	string strHeader;
	WxUser*Auth = (WxUser*)handle;

	int nCur = 0;

	//添加移动设备封包标志
	strHeader.push_back(0xbf);
	nCur++;
	
	//是否使用压缩算法(最后2bits)(1表示使用zlib压缩)(压缩后长度可能变长,不一定使用压缩算法)
	unsigned char SecondByte = (nLenProtobuf == nLenCompressed) ? 0x2 : 0x1;

	//包头长度最后写入
	strHeader.push_back(SecondByte);
	nCur++;

	//加密算法(前4bits),默认使用aes加密(5),需要rsa加密的CGI重载此虚函数
	unsigned char ThirdByte = 0x5 << 4;

	//cookie长度(后4bits)，当前协议默认15位
	ThirdByte += 0xf;

	strHeader.push_back(ThirdByte);
	nCur++;

	//写入版本号(大端4字节整数)
	DWORD dwVer = htonl(0x16070124);
	strHeader = strHeader + string((const char *)&dwVer,4);
	nCur += 4;

	//写入uin(大端4字节整数)
	DWORD dwUin = htonl(Auth->m_uin);
	strHeader = strHeader + string((const char *)&dwUin, 4);
	nCur += 4;

	//写入cookie
	strHeader = strHeader + Auth->m_cookie.c_str();
	nCur += 0xf;

	//cgi type(变长整数)
	string strCgi = Dword2String(cgiType);
	strHeader = strHeader + strCgi;
	nCur += strCgi.size();

	//protobuf长度(变长整数)
	string strProtobuf = Dword2String(nLenProtobuf);
	strHeader = strHeader + strProtobuf;
	nCur += strProtobuf.size();

	//protobuf压缩后长度(变长整数)
	string strCompressed = Dword2String(nLenCompressed);
	strHeader = strHeader + strCompressed;
	nCur += strCompressed.size();

	//ecdh校验值等mmtls协议才用到的参数(15 byte)(用0 补位)
	//string yw = Dword2String(10000);
	//strHeader = strHeader + yw;
	//nCur += yw.size();

	//strHeader = strHeader + string((const char *)2, 1);
	//nCur += 1;


	//string check = Dword2String(Auth->checkx);
	//strHeader = strHeader + check;
	//nCur += check.size();

	//string unknown = Dword2String(0x01004567);
	//strHeader = strHeader + unknown;
	//nCur += unknown.size();

	char szBuf[15] = { 0 };
	strHeader = strHeader + string(szBuf, 15);
	nCur += 15;

	//将包头长度写入第二字节前6bits(包头长度不会超出6bits)
	SecondByte += (nCur << 2);


	//将正确的第二字节写入包头
	strHeader[1] = SecondByte;

	return strHeader;
}

BaseHeader::HeaderInfo BaseHeader::UnPackHeader(void* Wx, string pack)
{
	string body;
	HeaderInfo info;

	WxUser*Auth = (WxUser*)Wx;
	int nCur = 0;

	if (pack.size() < 0x20)	return info;

	//跳过安卓标志bf(计入包头总长度)
	if (0xbf == (unsigned char)pack[nCur])
	{
		nCur++;
	}

	//解析包头长度(前6bits)
	info.nHeadLen = (unsigned char)pack[nCur] >> 2;

	//是否使用压缩(后2bits)
	info.bCompressed = (1 == ((unsigned char)pack[nCur] & 0x3)) ? TRUE : FALSE;

	nCur++;

	//解密算法(前4 bits)(05:aes / 07:rsa)(仅握手阶段的发包使用rsa公钥加密,由于没有私钥收包一律aes解密)
	info.nDecryptType = (unsigned char)pack[nCur] >> 4;

	//cookie长度(后4 bits)
	int nCookieLen = (unsigned char)pack[nCur] & 0xF;
	printf("CookieLen:%d", nCookieLen);
	nCur++;

	//服务器版本,无视(4字节)
	nCur += 4;

	//uin 非登录包,无视(4字节)
	nCur += 4;

	//刷新cookie(超过15字节说明协议头已更新)
	if (nCookieLen && nCookieLen <= 0xf)
	{
	
		Auth->m_cookie = pack.substr(nCur, nCookieLen);
		printf("CookieLen:%s", Auth->m_cookie.c_str());
		nCur += nCookieLen;
	}
	else if (nCookieLen > 0xf)
	{
		return info;
	}

	//cgi type,变长整数,无视
	DWORD dwLen = 0;
	DWORD dwCgiType = String2Dword(pack.substr(nCur, 5), dwLen);
	nCur += dwLen;

	//解压后protobuf长度，变长整数
	info.nLenRespProtobuf = String2Dword(pack.substr(nCur, 5), dwLen);
	//protoLen = (int)m_nLenRespProtobuf;
	nCur += dwLen;

	//压缩后(加密前)的protobuf长度，变长整数
	info.nLenRespCompressed = String2Dword(pack.substr(nCur, 5), dwLen);
	//compressed = (int)m_nLenRespCompressed;
	nCur += dwLen;

	//后面数据无视

	//解包完毕,取包体
	if (info.nHeadLen < pack.size())
	{
		info.body = pack.substr(info.nHeadLen);
	}

	return info;
}

std::string BaseHeader::LoginHead(int nLenProtobuf, int nLenCompressed)
{
	string strHeader;

	int nCur = 0;

	//登录包不需要添加移动设备封包标志
	//strHeader.push_back(0xbf);
	//nCur++;

	//登录包包体由三部分组成,不能直接使用压缩算法(最后2bits设为2)
	unsigned char SecondByte = 0x2;

	//包头长度最后写入
	strHeader.push_back(SecondByte);
	nCur++;

	//加密算法(前4bits),RSA加密(7)
	unsigned char ThirdByte = 0x7 << 4;

	//cookie长度(后4bits)，当前协议默认15位
	ThirdByte += 0xf;

	strHeader.push_back(ThirdByte);
	nCur++;

	DWORD dwVer = htonl(0x16070124);
	strHeader = strHeader + string((const char *)&dwVer, 4);
	nCur += 4;

	//登录包不需要uin 全0占位即可
	DWORD dwUin = 0;
	strHeader = strHeader + string((const char *)&dwUin, 4);
	nCur += 4;

	//登录包不需要cookie 全0占位即可
	char szCookie[15] = { 0 };
	strHeader = strHeader + string((const char *)szCookie, 15);
	nCur += 15;

	string strCgi = Dword2String(701);
	strHeader = strHeader + strCgi;
	nCur += strCgi.size();

	string strLenProtobuf = Dword2String(nLenProtobuf);
	strHeader = strHeader + strLenProtobuf;
	nCur += strLenProtobuf.size();

	string strLenCompressed = Dword2String(nLenCompressed);
	strHeader = strHeader + strLenCompressed;
	nCur += strLenCompressed.size();

	byte rsaVer = LOGIN_RSA_VER;
	strHeader = strHeader + string((const char *)&rsaVer, 1);
	nCur++;

	byte unkwnow[2] = { 0x01,0x02 };
	strHeader = strHeader + string((const char *)unkwnow, 2);
	nCur += 2;

	//将包头长度写入第二字节前6bits(包头长度不会超出6bits)
	SecondByte += (nCur << 2);

	//将正确的第二字节写入包头
	strHeader[0] = SecondByte;

	return strHeader;
}


std::string  BaseHeader::RsaHeader(int cgiType, int nLenProtobuf, int nLenCompressed, int nLenRsa)
{

	string strHeader;

	int nCur = 0;

	//移动设备封包标志
	strHeader.push_back(0xbf);
	nCur++;

	//protobuf压缩标志位
	unsigned char SecondByte = 0x1;

	//包头长度最后写入
	strHeader.push_back(SecondByte);
	nCur++;

	//加密算法(前4bits)
	unsigned char ThirdByte = 0x1 << 4;

	//cookie长度,写了也白写,不发送cookie
	ThirdByte += 0x0;

	strHeader.push_back(ThirdByte);
	nCur++;

	//版本号
	DWORD dwVer = htonl(0x16070124);
	strHeader = strHeader + string((const char *)&dwVer, 4);
	nCur += 4;

	//未登录成功时不需要uin 全0占位即可
	DWORD dwUin = 0;
	strHeader = strHeader + string((const char *)&dwUin, 4);
	nCur += 4;

	string strCgi = Dword2String(cgiType);
	strHeader = strHeader + strCgi;
	nCur += strCgi.size();

	string strLenProtobuf = Dword2String(nLenProtobuf);
	strHeader = strHeader + strLenProtobuf;
	nCur += strLenProtobuf.size();

	string strLenCompressed = Dword2String(nLenCompressed);
	strHeader = strHeader + strLenCompressed;
	nCur += strLenCompressed.size();

	byte rsaVer = LOGIN_RSA_VER;
	strHeader = strHeader + string((const char *)&rsaVer, 1);
	nCur++;

	byte unkwnow[2] = { 0x01,0x02 };
	strHeader = strHeader + string((const char *)unkwnow, 2);
	nCur += 2;

	//加密后数据长度
	string subHeader;
	short uLenProtobuf = nLenRsa;
	strHeader = strHeader + string((const char *)&uLenProtobuf, 2);
	nCur += 2;

	//毫无意义的5个字节(随意填写)
	char szUnknown[5] = { 0 };
	strHeader = strHeader + string((const char *)szUnknown, 5);
	nCur += 5;

	//将包头长度写入第二字节前6bits(包头长度不会超出6bits)
	SecondByte += (nCur << 2);

	//将正确的第二字节写入包头
	strHeader[1] = SecondByte;

	return strHeader;

}