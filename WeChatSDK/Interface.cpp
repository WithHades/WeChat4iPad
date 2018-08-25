#include "Interface.h"
#include "fun.h"
#include "mmCryptInterface.h"
#include <time.h>
#include <iostream>
#include "WeChatProto.h"
#include "PbHead.h"
#include "Taskk.h"
#include "TT.h"
#include "pbjson.hpp"
#include "MakeHeader.h"
#include "mm.pb.h"

#pragma comment(lib, "ws2_32.lib")  
#pragma comment(lib, "wldap32.lib")  
#pragma comment(lib, "libcurl.lib")  


void* WINAPI WxInitHandle(const char*IMEI, const char*deviceNAME, const char*deviceTYPE, const char*deviceUUID)
{
	curl_global_init(CURL_GLOBAL_WIN32);
	WxUser *auth;
	auth = (WxUser *)js_defaultalloc(0, NULL, sizeof *auth);
	auth = new WxUser();
	auth->s_IMEI = GetMd5_32(IMEI).c_str();

	time_t curtime = time(NULL);

	auth->changreqID = auth->s_IMEI + "-" + to_string(curtime);
	auth->s_deviceUUID = deviceUUID;
	auth->s_deviceTYPE =deviceTYPE;
	auth->s_deviceNAME = deviceNAME;
	auth->m_AesKey = GenAesKey();

	//CStringA deviceID = CStringA(GetMd5_32(deviceUUID).c_str());

	//auth->s_deviceID = Hex2bin(("49"+auth->s_IMEI.substr(2,30)).c_str());
	
	//string de = string_To_UTF8(Hex2bin("49aa7db2f4a3ffe0e96218f6b92cde32"));
	string de;
	//de = GetMd5_32(auth->s_deviceNAME + auth->s_deviceTYPE + auth->s_deviceUUID).c_str();
	//de = de.substr(2, 30);
	//de = ("49" + de).c_str();
	de =  Hex2bin("49aa7db2f4a3ffe0e96218f6b92cde32");

	string de15 = de;
	//de15.resize(15);

	auth->s_deviceID = de15;

	//auth->s_deviceID.resize(16);

	////auth->base->set_deviceid(realid.c_str());
	////auth->base->set_clientversion(637927472);
	////auth->base->set_devicetype(deviceTYPE);
	////auth->base->set_sessionkey("");


	cout << auth->s_deviceID.c_str() << endl;
	//cout << "Lenth:" << auth->m_guid.size() << endl;
	//auth->s_shortLink = "szshort.weixin.qq.com";
	//auth->s_longLink = "szlong.weixin.qq.com";

	return (void*)auth;
}


static void * JS_API js_defaultalloc(void *actx, void *ptr, int size)
{
	if (size == 0) {
		free(ptr);
		return NULL;
	}
	if (!ptr)
		return malloc((size_t)size);
	return realloc(ptr, (size_t)size);
}



std::string GenAesKey()
{
	string strAesKey;
	strAesKey.resize(16);
	for (int i = 0; i < 16; i++)
	{
		strAesKey[i] = rand() % 0xff;
	}
	
	return strAesKey.c_str();
}



void WINAPI WxGetQRCode(void*handle)
{
	string pb = PB_GetLoginQRCode(handle);
	WxUser*Auth = (WxUser*)handle;
	string pack = Encodeer(Auth, pb, RSA—πÀıº”√‹, CGI_TYPE_GETLOGINQRCODE,1);
	string url = "http://121.51.140.152";
	string ret = mm_post(url + CGI_GETLOGINQRCODE, pack);
	cout << ret.size() << endl;
	string RespProtobuf = DecodeEr(Auth, ret);

	micromsg::GetLoginQRCodeResponse resp;
	resp.ParseFromArray(RespProtobuf.c_str(), RespProtobuf.size());
	Auth->m_QrUUID = resp.uuid().c_str();
	Auth->m_notify = resp.notifykey().buffer().c_str();

	string json;
	pbjson::pb2json(&resp, json);

	FILE *fp = fopen("qq.txt", "a+");
	if (fp)
	{
		//string strNewMsg = Bin2Hex(json);
		fwrite(json.c_str(), 1, json.size(), fp);

		string strEnd = "\r\n";
		fwrite(strEnd.c_str(), 1, strEnd.size(), fp);

		fclose(fp);
	}
//	*pushStr = (char*)malloc(json.size() + 1);
//	memcpy(*pushStr, json.c_str(), json.size() + 1);
	QRCodeCallBack((void*)json.c_str(), CGI_TYPE_GETLOGINQRCODE);
	//cout << json.c_str() << endl;


	WxCheckQRCode(handle);

}


void WINAPI WxCheckQRCode(void*handle)
{
	string pb = PB_CheckLoginQRCode(handle);
	WxUser*Auth = (WxUser*)handle;
	string pack = Encodeer(Auth, pb, RSA—πÀıº”√‹, CGI_TYPE_CHECKLOGINQRCODE, 1);
	string url = "http://121.51.140.152";
	string ret = mm_post(url + CGI_CHECKLOGINQRCODE, pack);
	cout << ret.size() << endl;
	string RespProtobuf = DecodeEr(Auth, ret);

	micromsg::CheckLoginQRCodeResponse resp;
	resp.ParseFromArray(RespProtobuf.c_str(), RespProtobuf.size());
	
	std::string notifybuf = aes_nouncompress(Auth->m_notify, resp.notifypkg().notifydata().buffer());
	micromsg::LoginQRCodeNotify notifydata;
	notifydata.ParseFromArray(notifybuf.c_str(), notifybuf.size());

	string json;
	pbjson::pb2json(&notifydata, json);
	



	cout << json.c_str() << endl;
	pbjson::pb2json(&resp, json);
	QRCodeCallBack((void*)json.c_str(), CGI_TYPE_CHECKLOGINQRCODE);

	//*pushStr = (char*)malloc(json.size() + 1);
	//memcpy(*pushStr, json.c_str(), json.size() + 1);

	if (notifydata.status() < 2) 
	{
		WxCheckQRCode(handle);
		//free((void*)rrr);
	}
	else if (2 == notifydata.status()) 
	{
		Auth->m_UserName = notifydata.username().c_str();
		Auth->m_password = notifydata.pwd().c_str();
		if (Auth->m_UserName.size() && Auth->m_password.size())
		{
			Sleep(2000);
			WXQRCodeLogin(handle);

		}

	}
	


}


void WINAPI WXUserLogin(void*handle,const char*username, const char*password, char**pushStr)
{
	WxUser*Auth = (WxUser*)handle;
	Auth->loginType = ’À∫≈√‹¬Îµ«¬Ω;
	Auth->m_UserName = username;
	Auth->m_password = GetMd5_32(password);
	string RsaPb = PB_RsaLoginPart(handle);
	string RsaPb_x = Encodeer(handle, RsaPb, RSA—πÀıº”√‹, 0, 0);

	string AesPb = PB_AESLoginPart(handle);
	string AesPb_x = Encodeer(handle, AesPb, AES—πÀıº”√‹, 0, 0);

	string subHeader;
	DWORD dwLenAccountProtobuf = htonl(RsaPb.size());
	subHeader = subHeader + string((const char *)&dwLenAccountProtobuf, 4);
	DWORD dwLenDeviceProtobuf = htonl(AesPb.size());
	subHeader = subHeader + string((const char *)&dwLenDeviceProtobuf, 4);
	DWORD dwLenAccountRsa = htonl(RsaPb_x.size());
	subHeader = subHeader + string((const char *)&dwLenAccountRsa, 4);
	string body = subHeader + RsaPb_x + AesPb_x;
	BaseHeader head;
	string header = head.LoginHead(body.size(), body.size());
	string req = header + body;


	string url = "http://121.51.140.152";
	string ret = mm_post(url + CGI_MANUALAUTH, req);
	cout << ret.size() << endl;
	string RespProtobuf = DecodeEr(Auth, ret);
	micromsg::UnifyAuthResponse resp;
	resp.ParsePartialFromArray(RespProtobuf.c_str(), RespProtobuf.size());
	SaveInfo(resp.acctsectresp().username().c_str(), (void*)&resp);

	string json;
	micromsg::AcctSectResp acc;
	acc = resp.acctsectresp();
	pbjson::pb2json(&resp, json);
	//cout << json.c_str() << endl;
	if (0 == resp.baseresponse().ret())
	{
		Auth->m_uin = resp.authsectresp().uin();
		string key_s = resp.authsectresp().sessionkey().buffer().c_str();
		string SvrPubKey = resp.authsectresp().svrpubecdhkey().key().buffer();
		string ShakeKey = DoEcdh(713, SvrPubKey, Auth->ECDH_PriKey);
		Auth->m_AesKey = aes_nouncompress(ShakeKey, key_s);
		Auth->m_AuthKey = resp.authsectresp().authkey().c_str();
	}

	*pushStr = (char*)malloc(json.size() + 1);
	memcpy(*pushStr, json.c_str(), json.size() + 1);

}


void WINAPI WXQRCodeLogin(void*handle)
{
	WxUser*Auth = (WxUser*)handle;
	string RsaPb = PB_RsaLoginPart(handle);
	string RsaPb_x = Encodeer(handle, RsaPb, RSA—πÀıº”√‹, 0, 0);
		
	string AesPb = PB_AESLoginPart(handle);
	string AesPb_x = Encodeer(handle, AesPb, AES—πÀıº”√‹, 0, 0);

	string subHeader;
	DWORD dwLenAccountProtobuf = htonl(RsaPb.size());
	subHeader = subHeader + string((const char *)&dwLenAccountProtobuf, 4);
	DWORD dwLenDeviceProtobuf = htonl(AesPb.size());
	subHeader = subHeader + string((const char *)&dwLenDeviceProtobuf, 4);
	DWORD dwLenAccountRsa = htonl(RsaPb_x.size());
	subHeader = subHeader + string((const char *)&dwLenAccountRsa, 4);
	string body = subHeader + RsaPb_x + AesPb_x;	
	BaseHeader head;
	string header = head.LoginHead(body.size(), body.size());
	string req = header + body;


	string url = "http://121.51.140.152";
	string ret = mm_post(url + CGI_MANUALAUTH, req);
	cout << ret.size() << endl;
	string RespProtobuf = DecodeEr(Auth, ret);
	micromsg::UnifyAuthResponse resp;
	resp.ParsePartialFromArray(RespProtobuf.c_str(), RespProtobuf.size());
	SaveInfo(resp.acctsectresp().username().c_str(), (void*)&resp);

	for (int i = 0; i < resp.networksectresp().newhostlist().count(); i++)
	{
		cout<< resp.networksectresp().newhostlist().list(i).substitute().c_str();
	}
	resp.networksectresp().newhostlist().list(0).substitute().c_str();
	string json;
	micromsg::AcctSectResp acc;
	acc = resp.acctsectresp();
	pbjson::pb2json(&resp, json);
	//cout << json.c_str() << endl;
	if (0 == resp.baseresponse().ret())
	{
		Auth->m_uin = resp.authsectresp().uin();
		string key_s = resp.authsectresp().sessionkey().buffer().c_str();
		string SvrPubKey = resp.authsectresp().svrpubecdhkey().key().buffer();
		string ShakeKey = DoEcdh(713, SvrPubKey, Auth->ECDH_PriKey);
		printf("new aeskey:%s\n", Auth->m_AesKey.c_str());
		Auth->m_AesKey = aes_nouncompress(ShakeKey, key_s);
		printf("new aeskey:%s\n", Auth->m_AesKey.c_str());

		Auth->m_AuthKey = resp.authsectresp().authkey().c_str();
		Sleep(3000);
		WxNewInit(handle);
	}
//	*pushStr = (char*)malloc(json.size() + 1);
//	memcpy(*pushStr, json.c_str(), json.size() + 1);
	QRCodeCallBack((void*)json.c_str(),701);

}

void WINAPI WxNewInit(void*handle)
{
	WxUser*Auth = (WxUser*)handle;
	string InitPB = PB_NewInit(handle,Auth->m_AesKey);	

	string pack = Encodeer(handle, InitPB, AES—πÀıº”√‹, 139, 1);
	string url = "http://121.51.140.152";
	string ret = mm_post(url + CGI_NEWINIT, pack);
	string RespProtobuf = DecodeEr(Auth, ret);
	NewInitResponse resp;

	resp.ParseFromArray(RespProtobuf.c_str(), RespProtobuf.size());
	
	Auth->Sync_key = resp.sync_key_cur().c_str();
	string alljson;
	resp.cntlist();
	for (int i = 0; i < resp.cntlist(); i++)
	{
		if (1 == resp.tag7(i).type())
		{
			
		}
		else if (2 == resp.tag7(i).type())
		{
			contact_info contact;
			contact.ParsePartialFromArray(resp.tag7(i).data().data().c_str(), resp.tag7(i).data().data().size());
			string json;
			pbjson::pb2json(&contact, json);
			alljson = alljson + "," + json;
		}
		else if (5 == resp.tag7(i).type())
		{
			Msg m;
			m.ParsePartialFromArray(resp.tag7(i).data().data().c_str(), resp.tag7(i).data().data().size());
			string mjson;
			pbjson::pb2json(&m, mjson);
			alljson = alljson + "," + mjson;
		}


	}

	alljson = "[" + alljson + "]";

	//pbjson::pb2json(&InitB, json);
	//*pushStr = (char*)malloc(alljson.size() + 1);
	//memcpy(*pushStr, alljson.c_str(), alljson.size() + 1);

}

void WINAPI WxSyncMsg(void*handle, char**pushStr)
{
	WxUser*Auth = (WxUser*)handle;
	string sync = Auth->Sync_key;

	string pb = PB_NewSync(sync);
	Auth->Sync_key = sync;
	string aesbak = nocompress_aes(Auth->m_AesKey, pb);

	string pack = Encodeer(handle, pb, AES≤ª—πÀıº”√‹, 138, 1);
	string url = "http://121.51.140.152";
	string ret = mm_post(url + CGI_NEWSYNC, pack);
	string RespProtobuf = DecodeEr(Auth, ret);
	new_sync_resp resp;
	resp.ParseFromArray(RespProtobuf.c_str(), RespProtobuf.size());
	Auth->Sync_key = resp.sync_key();
	string alljson;
	for (int i = 0; i < resp.msg().cntlist(); i++)
	{
		if (5 == resp.msg().tag2(i).type())
		{
			Msg m;
			m.ParsePartialFromArray(resp.msg().tag2(i).data().data().c_str(), resp.msg().tag2(i).data().data().size());
			string mjson;
			pbjson::pb2json(&m, mjson);
			alljson = alljson + "," + mjson;
		}
		else if (2 == resp.msg().tag2(i).type())
		{
			contact_info contact;
			contact.ParsePartialFromArray(resp.msg().tag2(i).data().data().c_str(), resp.msg().tag2(i).data().data().size());
			string json;
			pbjson::pb2json(&contact, json);
			alljson = alljson + "," + json;
		}


	}

	alljson = "[" + alljson + "]";
	//pbjson::pb2json(&InitB, json);
	*pushStr = (char*)malloc(alljson.size() + 1);
	memcpy(*pushStr, alljson.c_str(), alljson.size() + 1);
}

void WINAPI SetQRCodeCallBack(QRCODECallBack callback)
{
	_qrcodeback = callback;

}

void WINAPI QRCodeCallBack(void*src,int cgi)
{
	if (_qrcodeback) 
	{
		_qrcodeback(src,cgi);
	}
}

void WINAPI testCheck()
{
	//WeiXin *wx = new WeiXin();
	//wx->DoConnect();
	//const char * re = wx->setshortlink("jdy11012");

	string pack = { 0x01,0x02 };
	string prikey = { 0x03, 0x04 };
	DWORD a = MMTLS_check(pack, 123456789, prikey);
	
}

void WINAPI SafeFree(void *p)
{
	__try
	{
		if (!p)
		{
			delete p;
			//delete p;
			p = NULL;
		}
	}
	__except (1)
	{
		cout << "[SafeFree]Crash!" << endl;
	}
}


void WINAPI SaveInfo(const char*username ,void* src)
{
	FILE *fp = fopen(username, "a+");
	if (fp)
	{
		string strNewMsg;
		micromsg::UnifyAuthResponse*resp = (micromsg::UnifyAuthResponse*)src;
		resp->SerializeToString(&strNewMsg);
		fwrite(strNewMsg.c_str(), 1, strNewMsg.size(), fp);

		fclose(fp);
	}

}




























































CURLcode curl_post_req(const string &url, const string &postParams, string &response)
{
	// init curl  
	CURL *curl = curl_easy_init();
	// res code  
	CURLcode res;
	if (curl)
	{
		// set params  
		curl_easy_setopt(curl, CURLOPT_POST, 1); // post req  
		
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); // url  
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postParams.c_str()); // params  
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, postParams.size()); // params  
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false); // if want to use https  
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false); // set peer and host verify false  
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
		curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, req_reply);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&response);
		curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
		curl_easy_setopt(curl, CURLOPT_HEADER, 1);
		curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3);
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3);
		//header
		struct curl_slist *headers = NULL;
		headers = curl_slist_append(headers, "Content-Type:application/octet-stream");
		headers = curl_slist_append(headers, "Accept:*/*");
		headers = curl_slist_append(headers, "User-Agent:MicroMessenger Client");
		headers = curl_slist_append(headers, "Host:hkshort.weixin.qq.com");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

		//curl_slist_free_all(headers);
		// start req  
		
		res = curl_easy_perform(curl);
		DWORD headsize = 0;
		curl_easy_getinfo(curl, CURLINFO_HEADER_SIZE, &headsize);
		response = response.substr(headsize);

	}
	// release curl  
	curl_easy_cleanup(curl);
	return res;
}

size_t req_reply(void *ptr, size_t size, size_t nmemb, void *stream)
{
	//cout << "----->reply" << endl;
	string *str = (string*)stream;
	//cout << *str << endl;
	(*str).append((char*)ptr, size*nmemb);
	return size * nmemb;
}


void WINAPI postLocal(std::string postParams)
{
	curl_global_init(CURL_GLOBAL_ALL);



	// test post requery  


	//string postParams = "f=8&rsv_bp=1&rsv_idx=1&word=picture&tn=98633779_hao_pg";
	std::string postResponseStr;
	auto res = curl_post_req("http://127.0.0.1:8888", postParams, postResponseStr);


	//if (res != CURLE_OK)
	//	cerr << "curl_easy_perform() failed: " + string(curl_easy_strerror(res)) << endl;
	//else
	//	cout << postResponseStr << endl;

	// global release  
	curl_global_cleanup();
	//system("pause");
	return ;
}


std::string mm_post(std::string url_post, std::string postParams)
{
	// global init  
	curl_global_init(CURL_GLOBAL_ALL);



	// test post requery  


	//string postParams = "f=8&rsv_bp=1&rsv_idx=1&word=picture&tn=98633779_hao_pg";
	std::string postResponseStr;
	auto res = curl_post_req(url_post, postParams, postResponseStr);
	

	//if (res != CURLE_OK)
	//	cerr << "curl_easy_perform() failed: " + string(curl_easy_strerror(res)) << endl;
	//else
	//	cout << postResponseStr << endl;

	// global release  
	curl_global_cleanup();
	//system("pause");
	return postResponseStr;
}