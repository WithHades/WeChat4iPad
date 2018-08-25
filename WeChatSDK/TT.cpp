#include "TT.h"
#include "fun.h"
#include "windows/zlib/adler32.h"
//1,加密(压缩或者不压缩)

//2.组包头-->


#include "stdafx.h"

string Encodeer(void*handle, string src, int Type, int ID_cgi, int NeedHead)
{
	
	if (!src.size()) return "";
	WxUser*Auth = (WxUser*)handle;
	
	if (Type == AES压缩加密)
	{
		DWORD compressedLen = 0;

		string ZipPack = IntoCompress(src);
	
		string AesPack = nocompress_aes(Auth->m_AesKey, ZipPack);
		if (NeedHead)
		{
			
			string head;
			
			const unsigned char front[] = { 0xBF, 0x00, 0x00, 0x16, 0x07, 0x01, 0x24 };
			const unsigned char endtag[] = { 0x02 };
			DWORD check = MMTLS_check(src, Auth->m_uin, Auth->ECDH_PriKey);	
			DWORD dwUin = htonl(Auth->m_uin);

			head = head + string((const char*)front, 7)
				+ string((const char *)&dwUin, 4)
				+ Auth->m_cookie
				+ Dword2String(ID_cgi)
				+ Dword2String(src.size())
				+ Dword2String(AesPack.size())
				+ Dword2String(10000)
				+ string((const char*)endtag)
				+ Dword2String((int)check)
				+ Dword2String(0x01004567);
			
			int HeadLen = head.size();
			printf("插入前:\n%s\n" ,Bin2Hex(head).c_str());
			head[1] = (unsigned char)((byte)((HeadLen * 4) + 1));
			head[2] = (unsigned char)((byte)(0x50 + Auth->m_cookie.size()));
			//head[3] = (unsigned char)(Auth->m_cookie.size());
			printf("插入后:\n%s\n", Bin2Hex(head).c_str());
			string rep;
			rep = head + AesPack;

			printf("结合后:\n%s\n", Bin2Hex(rep).c_str());
			
			return rep;
			//string oldrep;

			//string strHeader;
			//int nCur = 0;

			////添加移动设备封包标志
			//strHeader.push_back(0xbf);
			//nCur++;

			////是否使用压缩算法(最后2bits)(1表示使用zlib压缩)(压缩后长度可能变长,不一定使用压缩算法)
			//unsigned char SecondByte = (src.size() == AesPack.size()) ? 0x2 : 0x1;

			////包头长度最后写入
			//strHeader.push_back(SecondByte);
			//nCur++;

			////加密算法(前4bits),默认使用aes加密(5),需要rsa加密的CGI重载此虚函数
			//unsigned char ThirdByte = 0x5 << 4;

			////cookie长度(后4bits)，当前协议默认15位
			//ThirdByte += 0xf;

			//strHeader.push_back(ThirdByte);
			//nCur++;

			////写入版本号(大端4字节整数)
			//DWORD dwVer = htonl(0x16070124);
			//strHeader = strHeader + string((const char *)&dwVer, 4);
			//nCur += 4;

			////写入uin(大端4字节整数)
			//DWORD dwUinx = htonl(Auth->m_uin);
			//strHeader = strHeader + string((const char *)&dwUinx, 4);
			//nCur += 4;

			////写入cookie
			//strHeader = strHeader + Auth->m_cookie;
			//nCur += 0xf;

			////cgi type(变长整数)
			//string strCgi = Dword2String(ID_cgi);
			//strHeader = strHeader + strCgi;
			//nCur += strCgi.size();

			////protobuf长度(变长整数)
			//string strProtobuf = Dword2String(src.size());
			//strHeader = strHeader + strProtobuf;
			//nCur += strProtobuf.size();

			////protobuf压缩后长度(变长整数)
			//string strCompressed = Dword2String(AesPack.size());
			//strHeader = strHeader + strCompressed;
			//nCur += strCompressed.size();

			////ecdh校验值等mmtls协议才用到的参数(15 byte)(用0 补位)
			//char szBuf[15] = { 0 };
			//strHeader = strHeader + string(szBuf, 15);
			//nCur += 15;

			////将包头长度写入第二字节前6bits(包头长度不会超出6bits)
			//SecondByte += (nCur << 2);


			////将正确的第二字节写入包头
			//strHeader[1] = SecondByte;
			//printf("旧头头:\n%s\n", Bin2Hex(strHeader).c_str());

			//oldrep = strHeader + AesPack;
			//printf("身体:\n%s\n", Bin2Hex(oldrep).c_str());
			
	

		}
		else
		{
			return AesPack;
		}
	}
	else if (Type == AES不压缩加密)
	{
		string AesPack = nocompress_aes(Auth->m_AesKey, src);

		if (NeedHead)
		{

			//BaseHeader head;
			//printf("加密前长度：%d,加密后长度：%d，cookie：%s", src.size(), AesPack.size(), Auth->m_cookie.c_str());
			//string headPack = head.MakeHeader(handle, ID_cgi, src.size(), AesPack.size());
			string oldrep;

			string strHeader;
			int nCur = 0;

			//添加移动设备封包标志
			strHeader.push_back(0xbf);
			nCur++;

			//是否使用压缩算法(最后2bits)(1表示使用zlib压缩)(压缩后长度可能变长,不一定使用压缩算法)
			unsigned char SecondByte = (src.size() == AesPack.size()) ? 0x2 : 0x1;

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
			strHeader = strHeader + string((const char *)&dwVer, 4);
			nCur += 4;

			//写入uin(大端4字节整数)
			DWORD dwUinx = htonl(Auth->m_uin);
			strHeader = strHeader + string((const char *)&dwUinx, 4);
			nCur += 4;

			//写入cookie
			strHeader = strHeader + Auth->m_cookie;
			nCur += 0xf;

			//cgi type(变长整数)
			string strCgi = Dword2String(ID_cgi);
			strHeader = strHeader + strCgi;
			nCur += strCgi.size();

			//protobuf长度(变长整数)
			string strProtobuf = Dword2String(src.size());
			strHeader = strHeader + strProtobuf;
			nCur += strProtobuf.size();

			//protobuf压缩后长度(变长整数)
			string strCompressed = Dword2String(AesPack.size());
			strHeader = strHeader + strCompressed;
			nCur += strCompressed.size();

			//ecdh校验值等mmtls协议才用到的参数(15 byte)(用0 补位)
			char szBuf[15] = { 0 };
			strHeader = strHeader + string(szBuf, 15);
			nCur += 15;

			//将包头长度写入第二字节前6bits(包头长度不会超出6bits)
			SecondByte += (nCur << 2);


			//将正确的第二字节写入包头
			strHeader[1] = SecondByte;
			printf("旧头头:\n%s\n", Bin2Hex(strHeader).c_str());

			oldrep = strHeader + AesPack;
			printf("身体:\n%s\n", Bin2Hex(oldrep).c_str());

			return oldrep;

		}
		else 
		{
			return AesPack;
		}

	}
	else if (Type == RSA压缩加密)
	{
		string keye = Hex2bin(LOGIN_RSA_VER158_KEY_E);
		string keyn = Hex2bin(LOGIN_RSA_VER158_KEY_N);
		DWORD dwCompressed = 0;
		string reqbuf = compress_rsa(keye, keyn, src, dwCompressed);

		if (NeedHead)
		{
			BaseHeader head;
			string header = head.RsaHeader(ID_cgi, src.size(), dwCompressed, reqbuf.size());
			return header + reqbuf;

		}
		else
		{
			return reqbuf;
		}


	


	}

	return "";

}



unsigned long MMTLS_check(string Pack ,int m_uin,string PriKey)
{
	DWORD dwUin = htonl(m_uin);
	string ww = string((const char *)&dwUin, 4);
	ww = ww + PriKey;
	string md5 = GetMd5(ww);	
	//printf("MD5:%s\n", md5.c_str());
	DWORD pLen = htonl(Pack.size());
	string yy = string((const char*)&pLen, 4);
	//printf("yy:%s\n", yy.c_str());
	string kk = GetMd5(yy + PriKey+md5);

	DWORD check = _adler32(1,(const unsigned char*)kk.c_str(), kk.size());
	check = _adler32(check, (const unsigned char*)Pack.c_str(), Pack.size());
	return check;
}




std::string DecodeEr(void*handle, string src)
{
	BaseHeader head;
	WxUser*Auth = (WxUser*)handle;
	BaseHeader::HeaderInfo info; 
	info = head.UnPackHeader(handle, src);

	string RespProtobuf;
	bool iRet = info.bCompressed;
	if (iRet)
	{
		RespProtobuf = aes_uncompress(Auth->m_AesKey, info.body, info.nLenRespProtobuf);
	}
	else
	{
		RespProtobuf = aes_nouncompress(Auth->m_AesKey, info.body);
	}

	return RespProtobuf;

}