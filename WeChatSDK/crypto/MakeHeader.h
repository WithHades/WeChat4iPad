#pragma once
#include <string>
using namespace std;




class BaseHeader
{
public:
	struct HeaderInfo
	{
		DWORD		nLenRespCompressed;
		DWORD		nLenRespProtobuf;
		int		nHeadLen;
		int		nDecryptType;
		bool	bCompressed;
		string  body;
	};

	std::string MakeHeader(void*,int cgiType,int nLenProtobuf,int nLenCompressed);
	HeaderInfo UnPackHeader(void* Wx, string pack);
	std::string RsaHeader(int cgiType, int nLenProtobuf, int nLenCompressed, int nLenRsa);

	std::string LoginHead(int nLenProtobuf, int nLenCompressed);






};
