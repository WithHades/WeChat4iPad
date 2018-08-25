#pragma once
#include <string>
//#include "db/db.h"
#define ÕËºÅÃÜÂëµÇÂ½ 1
#define ¶şÎ¬ÂëµÇÂ½	2	
#define ÊÖ»úºÅÂëµÇÂ½	3


using namespace std;
#define CLIENT_VERSION  0x16070124
class WxUser
{
public:
	WxUser();
	~WxUser();
public:
	string ECDH_PubKey;
	string ECDH_PriKey;
	int checkx;
	string  m_AesKey;
	string	m_UserName;
	string m_password;
	string s_IMEI;
	string changreqID;
	string s_deviceUUID;
	string s_deviceTYPE;
	string s_deviceNAME;
	string	m_WxId;
	int   m_uin;
	string	m_Alias;
	int loginType;
	int   m_ClientVersion;

	string  s_deviceID;
	string  m_AuthKey;
	string  m_androidVer;
	string  m_launguage;
	string  m_cookie;
	string	m_QrUUID;
	string  m_notify;
	string	Sync_key;
	
	string ShortLink;
	string LongLink;


};

