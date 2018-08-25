#include "WeChatProto.h"
#include <time.h>
#include "pbjson.hpp"
#include "mmCryptInterface.h"
#include "fun.h"
#include "mm.pb.h"
#include "Proto/WeDA.pb.h"



std::string PB_GetLoginQRCode(void*Au)
{
	std::string src;
	micromsg::GetLoginQRCodeRequest Req;
	WxUser*Auth = (WxUser*)Au;
	micromsg::BaseRequest *Base = new micromsg::BaseRequest();
	Base->set_clientversion(0x16070124);
	Base->set_deviceid(Auth->s_deviceID.c_str());
	Base->set_devicetype("iPad iPhone OS8.4");
	Base->set_scene(1);
	Base->set_uin(0);
	Base->set_sessionkey("");
	micromsg::SKBuiltinBuffer_t *AesKey = new micromsg::SKBuiltinBuffer_t();
	AesKey->set_buffer(Auth->m_AesKey.c_str());
	AesKey->set_ilen(16);
	Req.set_allocated_baserequest(Base);// id->1
	Req.set_allocated_randomencrykey(AesKey);	// id->2
	Req.set_opcode(0);// id->3
	Req.SerializeToString(&src);
	Req.release_baserequest();
	Req.release_randomencrykey();
	string testjson;
	pbjson::pb2json(&Req,testjson);
	
	return src;

}
std::string PB_CheckLoginQRCode(void*Au)
{
	std::string src;
	WxUser*Auth = (WxUser*)Au;
	micromsg::CheckLoginQRCodeRequest req;
	micromsg::BaseRequest *Base = new micromsg::BaseRequest();
	Base->set_clientversion(0x16070124);
	Base->set_deviceid(Auth->s_deviceID.c_str());
	Base->set_devicetype("iPad iPhone OS8.4");
	Base->set_scene(0);
	Base->set_uin(0);
	Base->set_sessionkey("");
	micromsg::SKBuiltinBuffer_t *AesKey = new micromsg::SKBuiltinBuffer_t();
	AesKey->set_buffer(Auth->m_AesKey.c_str());
	AesKey->set_ilen(16);

	req.set_allocated_baserequest(Base);
	req.set_allocated_randomencrykey(AesKey);
	req.set_uuid(Auth->m_QrUUID.c_str());
	req.set_opcode(0);
	time_t curtime = time(NULL);
	req.set_timestamp((int)curtime);
	req.SerializeToString(&src);
	req.release_baserequest();
	req.release_randomencrykey();

	return src;
}



std::string PB_RsaLoginPart(void*Au)
{
	string req;
	micromsg::ManualAuthRsaReqData accountQuest;

	micromsg::SKBuiltinBuffer_t  *aesKey = new micromsg::SKBuiltinBuffer_t();

	micromsg::ECDHKey *ecdh = new micromsg::ECDHKey;
	micromsg::SKBuiltinBuffer_t *ecdhKey = new micromsg::SKBuiltinBuffer_t;

	WxUser*Auth = (WxUser*)Au;
	GenEcdh(713, Auth->ECDH_PubKey, Auth->ECDH_PriKey);

	aesKey->set_ilen(16);
	aesKey->set_buffer(Auth->m_AesKey.c_str());
	ecdhKey->set_ilen(Auth->ECDH_PubKey.size());
	ecdhKey->set_buffer(Auth->ECDH_PubKey);
	ecdh->set_allocated_key(ecdhKey);
	ecdh->set_nid(713);

	accountQuest.set_allocated_randomencrykey(aesKey);
	accountQuest.set_allocated_clipubecdhkey(ecdh);

	accountQuest.set_username(Auth->m_UserName.c_str());
	accountQuest.set_pwd(Auth->m_password.c_str());
	if (Auth->loginType == 账号密码登陆) {
		accountQuest.set_pwd2(Auth->m_password.c_str());
	}
	//

	accountQuest.SerializeToString(&req);

	accountQuest.release_randomencrykey();
	accountQuest.release_clipubecdhkey();
	ecdh->release_key();
	delete aesKey;
	delete ecdh;
	delete ecdhKey;

	return req;
}
std::string PB_AESLoginPart(void*Au)
{

	string req;
	//com::tencent::mars::sample::proto::ManualAuthDeviceRequest deviceQuest;
	micromsg::ManualAuthAesReqData deviceQuest;
	micromsg::BaseRequest*loginInfo = new micromsg::BaseRequest();
	/*micromsg::BaseAuthReqInfo *BaseAuthReqInfo = new micromsg::BaseAuthReqInfo();
	micromsg::WTLoginImgReqInfo *WTLoginImgReqInfo_ = new micromsg::WTLoginImgReqInfo();
	micromsg::WxVerifyCodeReqInfo *WxVerifyCodeReqInfo_ = new micromsg::WxVerifyCodeReqInfo();
	micromsg::SKBuiltinBuffer_t *CliDBEncryptKey = new micromsg::SKBuiltinBuffer_t();
	micromsg::SKBuiltinBuffer_t *CliDBEncryptInfo = new micromsg::SKBuiltinBuffer_t();
	micromsg::SKBuiltinBuffer_t *WTLoginReqBuff = new micromsg::SKBuiltinBuffer_t();
	micromsg::SKBuiltinBuffer_t *KSid = new micromsg::SKBuiltinBuffer_t();
	
	*/
	//clientdata->set_buffer(string(""));
	//clientdata->set_ilen(0);
	
	WxUser*Auth = (WxUser*)Au;
	//data = Hex2bin("0A310A0010001A1049AA7DB2F4A3FFE0E96218F6B92CDE3220A08E98B0012A1169506164206950686F6E65204F53382E34300112023A001A203363616137646232663461336666653065393632313866366239326364653332228D023C736F6674747970653E3C6B333E382E343C2F6B333E3C6B393E695061643C2F6B393E3C6B31303E323C2F6B31303E3C6B31393E45313841454344332D453630422D344635332D423838372D4339343436344437303836393C2F6B31393E3C6B32303E3C2F6B32303E3C6B32313E313030333C2F6B32313E3C6B32323E286E756C6C293C2F6B32323E3C6B32343E62383A66383A38333A33393A61643A62393C2F6B32343E3C6B33333EE5BEAEE4BFA13C2F6B33333E3C6B34373E313C2F6B34373E3C6B35303E313C2F6B35303E3C6B35313E6461697669732E495041443C2F6B35313E3C6B35343E69506164322C353C2F6B35343E3C6B36313E323C2F6B36313E3C2F736F6674747970653E2800322B33636161376462326634613366666530653936323138663662393263646533322D313532383535343230314204695061644A046950616452057A685F434E5A04382E3030680070AFC6EFD8057A054170706C65920102434E9A010B6461697669732E49504144AA010769506164322C35B00102BA01D50608CF0612CF060A08303030303030303310011AC0068A8DCEEE5AB9F4E16054EDA0545F7288B7951621A41446C1AEC0621B3CFE6926737F8298D0B52F467FDFC5EC936D512D332A1AC664E7DFEE734A5E403A72225F852734BF32F6FD623B95D17B64DC8D18FBB2CA2015113CD17518274BED4687D26F5D9E270687745541FA84921A16B50CFE487B1A88C3A91D838A2520AF8757F0E5ACE55BA599B9FCDF1595C3DAAD8E3A34C28BA39951D7A4CF9075CCC28721BA61E48C2DA1B853F3BE0D79AC63F47F2E3C4FF10D4D1CCC1D3002B6F63C228641C1EEB24686BA300853C355C268057D733B7898D20E6B43621419D8BCFCAED82C45377653234B7421238D00B25089670DDEBB03274B1D0D8C45D5A0EA7ECA9086254CCEAA8674ADE4DF905914437BC73D4C9D50CEC9ABCB927590D068DC10A810D376DAFB17A31F947765FF6A7F3B191EC40EEC4AA86FF8771CD2D717D25EE2B7555179AF4C611B9C6AD802B8FDAEAE36CA3497C438E8D4A06B1A7A570D74AAF6C244E8D23BA635FF0F27DCFCF5F6C4754A0049A620AE99012EB4936D34BAD267EAFDB12B67D5274272D3BC795B6454B4C2B768929007D0993F742A519D567ACD0369FCC9196D3CC04578F795026C336F2A29A012608C66E2068F5994210173C5A3B2720A4D040A6D2C3E873D56CE88F85CEFE4847743DEF1102653D42FBC3A31CA5BFE2E666D3542E6E1C5BCCE54D99EC934B183EED69FEA87D975666065E5903F366EFFE04627603FD64861C142A5A19EBD344BF194DE427FB4B70AA0D3CD972AC0A11EA6913E17366CA48966090E10B246BABABA553DBF89BEA4F55004C37E546ABABB8AA20E80B2A0ED21B6700F89699FD01983EDA71ACE6A44B6397605D30E88683BA4BB92A50DC7AFFB820089F157B8C83F7B5DCD35BABCC90501E2E6BDF83327A1059908C72EAF1B5A07CA6565A0888883966D26386C69293649BEC0913FE12C1ABA7B0B16261176E2F7D109FCF68A46B7C3AF7126E77224AA36891B703655CFEA2AAA8B5E095D8B204308133E63D0F0309E8B1CB5A21E9C8B27090859139C076723DE4C74578F6584888220A11A45CDDEC43A1F542552604C96FFE3A01006946086A864C182361B3659C1BDE9ECEA5236F5F38BA98A4C7E8C81A39D5CBA39B7A0F9FFA75AC59BB956595B58DAED58A0851D48B0B7A7407FA576E4956C");

	//deviceQuest.ParseFromArray(data.c_str(), data.size());
	//CliDBEncryptKey->set_ilen(0);
	//CliDBEncryptInfo->set_ilen(0);
	//WTLoginReqBuff->set_ilen(0);
	//KSid->set_ilen(0);
	//WTLoginImgReqInfo_->set_allocated_ksid(KSid);

	//m::tencent::mars::sample::proto::ManualAuthDeviceRequest_LoginInfo *loginInfo = new com::tencent::mars::sample::proto::ManualAuthDeviceRequest_LoginInfo;

	//com::tencent::mars::sample::proto::ManualAuthDeviceRequest_UnknowInfo2  *unknownInfo2 = new com::tencent::mars::sample::proto::ManualAuthDeviceRequest_UnknowInfo2;
	//com::tencent::mars::sample::proto::ManualAuthDeviceRequest_UnknowInfo2_Tag1 *tag1 = new com::tencent::mars::sample::proto::ManualAuthDeviceRequest_UnknowInfo2_Tag1;
	//com::tencent::mars::sample::proto::ManualAuthDeviceRequest_UnknowInfo2_Tag2 *tag2 = new com::tencent::mars::sample::proto::ManualAuthDeviceRequest_UnknowInfo2_Tag2;
	//com::tencent::mars::sample::proto::ManualAuthDeviceRequest_UnknowInfo2_Tag2_Tag4 *tag2_tag4 = new com::tencent::mars::sample::proto::ManualAuthDeviceRequest_UnknowInfo2_Tag2_Tag4;
	//tag2->set_allocated_tag4(tag2_tag4);
	//com::tencent::mars::sample::proto::ManualAuthDeviceRequest_UnknowInfo2_Tag3 *tag3 = new com::tencent::mars::sample::proto::ManualAuthDeviceRequest_UnknowInfo2_Tag3;
	//com::tencent::mars::sample::proto::ManualAuthDeviceRequest_UnknowInfo2_Tag4 *tag4 = new com::tencent::mars::sample::proto::ManualAuthDeviceRequest_UnknowInfo2_Tag4;
	//com::tencent::mars::sample::proto::ManualAuthDeviceRequest_UnknowInfo2_Tag5 *tag5 = new com::tencent::mars::sample::proto::ManualAuthDeviceRequest_UnknowInfo2_Tag5;
//	BaseAuthReqInfo->set_allocated_clidbencryptinfo(CliDBEncryptInfo);
	//BaseAuthReqInfo->set_allocated_wtloginimgreqinfo(WTLoginImgReqInfo_);
//	BaseAuthReqInfo->set_allocated_clidbencryptkey(CliDBEncryptKey);
	//BaseAuthReqInfo->set_allocated_wxverifycodereqinfo(WxVerifyCodeReqInfo_);
	//BaseAuthReqInfo->set_allocated_wtloginreqbuff(WTLoginReqBuff);
	////BaseAuthReqInfo->set_authreqflag(0);
	//BaseAuthReqInfo->set_authticket("");
	


	//CStringA strSoftInfo;
	//strSoftInfo.Format(DEVICE_INFO_SOFTINFO, DEVICE_INFO_IMEI,DEVICE_INFO_ANDROID_ID, DEVICE_INFO_MANUFACTURER+" "+DEVICE_INFO_MODELNAME, DEVICE_INFO_MOBILE_WIFI_MAC_ADDRESS, DEVICE_INFO_CLIENT_SEQID_SIGN, DEVICE_INFO_AP_BSSID, DEVICE_INFO_MANUFACTURER,"taurus", DEVICE_INFO_MODELNAME, DEVICE_INFO_IMEI);
	/*
	
	
	
	
    */
	time_t curtime = time(NULL);
	string data = Hex2bin("0A310A0010001A1049AA7DB2F4A3FFE0E96218F6B92CDE3220A08E98B0012A1169506164206950686F6E65204F53382E34300112023A001A203363616137646232663461336666653065393632313866366239326364653332228D023C736F6674747970653E3C6B333E382E343C2F6B333E3C6B393E695061643C2F6B393E3C6B31303E323C2F6B31303E3C6B31393E45313841454344332D453630422D344635332D423838372D4339343436344437303836393C2F6B31393E3C6B32303E3C2F6B32303E3C6B32313E313030333C2F6B32313E3C6B32323E286E756C6C293C2F6B32323E3C6B32343E62383A66383A38333A33393A61643A62393C2F6B32343E3C6B33333EE5BEAEE4BFA13C2F6B33333E3C6B34373E313C2F6B34373E3C6B35303E313C2F6B35303E3C6B35313E6461697669732E495041443C2F6B35313E3C6B35343E69506164322C353C2F6B35343E3C6B36313E323C2F6B36313E3C2F736F6674747970653E2800322B33636161376462326634613366666530653936323138663662393263646533322D313532383535343230314204695061644A046950616452057A685F434E5A04382E3030680070AFC6EFD8057A054170706C65920102434E9A010B6461697669732E49504144AA010769506164322C35B00102BA01D50608CF0612CF060A08303030303030303310011AC0068A8DCEEE5AB9F4E16054EDA0545F7288B7951621A41446C1AEC0621B3CFE6926737F8298D0B52F467FDFC5EC936D512D332A1AC664E7DFEE734A5E403A72225F852734BF32F6FD623B95D17B64DC8D18FBB2CA2015113CD17518274BED4687D26F5D9E270687745541FA84921A16B50CFE487B1A88C3A91D838A2520AF8757F0E5ACE55BA599B9FCDF1595C3DAAD8E3A34C28BA39951D7A4CF9075CCC28721BA61E48C2DA1B853F3BE0D79AC63F47F2E3C4FF10D4D1CCC1D3002B6F63C228641C1EEB24686BA300853C355C268057D733B7898D20E6B43621419D8BCFCAED82C45377653234B7421238D00B25089670DDEBB03274B1D0D8C45D5A0EA7ECA9086254CCEAA8674ADE4DF905914437BC73D4C9D50CEC9ABCB927590D068DC10A810D376DAFB17A31F947765FF6A7F3B191EC40EEC4AA86FF8771CD2D717D25EE2B7555179AF4C611B9C6AD802B8FDAEAE36CA3497C438E8D4A06B1A7A570D74AAF6C244E8D23BA635FF0F27DCFCF5F6C4754A0049A620AE99012EB4936D34BAD267EAFDB12B67D5274272D3BC795B6454B4C2B768929007D0993F742A519D567ACD0369FCC9196D3CC04578F795026C336F2A29A012608C66E2068F5994210173C5A3B2720A4D040A6D2C3E873D56CE88F85CEFE4847743DEF1102653D42FBC3A31CA5BFE2E666D3542E6E1C5BCCE54D99EC934B183EED69FEA87D975666065E5903F366EFFE04627603FD64861C142A5A19EBD344BF194DE427FB4B70AA0D3CD972AC0A11EA6913E17366CA48966090E10B246BABABA553DBF89BEA4F55004C37E546ABABB8AA20E80B2A0ED21B6700F89699FD01983EDA71ACE6A44B6397605D30E88683BA4BB92A50DC7AFFB820089F157B8C83F7B5DCD35BABCC90501E2E6BDF83327A1059908C72EAF1B5A07CA6565A0888883966D26386C69293649BEC0913FE12C1ABA7B0B16261176E2F7D109FCF68A46B7C3AF7126E77224AA36891B703655CFEA2AAA8B5E095D8B204308133E63D0F0309E8B1CB5A21E9C8B27090859139C076723DE4C74578F6584888220A11A45CDDEC43A1F542552604C96FFE3A01006946086A864C182361B3659C1BDE9ECEA5236F5F38BA98A4C7E8C81A39D5CBA39B7A0F9FFA75AC59BB956595B58DAED58A0851D48B0B7A7407FA576E4956C");
	
	deviceQuest.ParseFromArray( data.c_str() , data.size() );

	micromsg::SKBuiltinBuffer_t *clientdata = new micromsg::SKBuiltinBuffer_t();
	clientdata->set_buffer(string(""));
	clientdata->set_ilen(0);
	loginInfo->set_sessionkey(Auth->m_AesKey.c_str());
	loginInfo->set_uin(0);
	//string guid15 = string(Auth->m_deviceid.c_str(), 15);

	loginInfo->set_deviceid(Auth->s_deviceID.c_str());
	loginInfo->set_clientversion(0x16070124);
	loginInfo->set_devicetype("iPad iPhone OS8.4");

	loginInfo->set_scene(0);
	deviceQuest.set_allocated_baserequest(loginInfo);
	deviceQuest.set_softtype("<softtype><k3>8.4</k3><k9>iPad</k9><k10>2</k10><k19>E18AECD3-E60B-4F53-B887-C94464D70869</k19><k20></k20><k21>1003</k21><k22>(null)</k22><k24>b8:f8:83:39:ad:b9</k24><k33>寰俊</k33><k47>1</k47><k50>1</k50><k51>com.tencent.xin</k51><k54>iPad2,5</k54><k61>2</k61></softtype>");
	deviceQuest.set_bundleid("com.tencent.xin");
	deviceQuest.set_timestamp((int)curtime);
	deviceQuest.set_allocated_clientcheckdat(clientdata);
	deviceQuest.set_imei(Auth->s_IMEI.c_str());
	char buf[30];
	_itoa((int)curtime, buf, 10);
	string meid = Auth->s_IMEI + "-" + buf;
	deviceQuest.set_clientseqid(meid.c_str());
	
	/*
	manualAuthDeviceRequest.Timestamp = (int)CurrentTime_();
	manualAuthDeviceRequest.Clientcheckdat = new SKBuiltinString_(){ buffer = new byte[]{}, iLen = 0 };
	manualAuthDeviceRequest.imei = Encoding.UTF8.GetBytes("85aa7db2f4a3ffe0e96218f6b92cde32");
	manualAuthDeviceRequest.clientSeqID = manualAuthDeviceRequest.imei + "-" + ((int)CurrentTime_()).ToString();
	manualAuthDeviceRequest.baseRequest = GetBaseRequest(0);



	*/
	//CStringA strDeviceInfo;
	//strDeviceInfo.Format(DEVICE_INFO_DEVICEINFO, DEVICE_INFO_MANUFACTURER, DEVICE_INFO_MODELNAME);

	//deviceQuest.set_allocated_baserequest(loginInfo);
	//deviceQuest.set_allocated_basereqinfo(BaseAuthReqInfo);
	//string s_imei = Auth->s_IMEI.c_str();


	//char buf[30];
	//_itoa((int)curtime, buf, 10);
	//string meid = GetMd5_32(s_imei) + "-" + buf;

	//deviceQuest.set_imei(GetMd5_32(s_imei).c_str());
	//deviceQuest.set_softtype(Auth->s_deviceTYPE.c_str());
	//deviceQuest.set_builtinipseq(0);

	//deviceQuest.set_clientseqid(meid.c_str());
	////deviceQuest.set_clientseqid_sign(GetMd5_32(Auth->m_deviceid.c_str()).c_str());
	//deviceQuest.set_devicename(Auth->s_deviceNAME.c_str());
	////deviceQuest.set_devicetype("iPad iPhone OS9.0.2");
	//deviceQuest.set_language("zh_CN");
	//deviceQuest.set_timezone("8.00");
	//deviceQuest.set_channel(0);

	//deviceQuest.set_timestamp((int)curtime);
	//deviceQuest.set_devicebrand("Apple");
	////deviceQuest.set_devicemodel("iPad mini 2 (Wi-Fi)");
	//deviceQuest.set_ostype("iPad iPhone OS9.0.2");
	//deviceQuest.set_iphonever("iPad4.4");
	//deviceQuest.set_realcountry("cn");
	//deviceQuest.set_bundleid("com.tencent.xin");
	//deviceQuest.set_inputtype(2);

	deviceQuest.SerializeToString(&req);

	//BaseAuthReqInfo->release_clidbencryptinfo();
	//BaseAuthReqInfo->release_clidbencryptkey();
	//BaseAuthReqInfo->release_wtloginimgreqinfo();
	//BaseAuthReqInfo->release_wtloginreqbuff();
	//BaseAuthReqInfo->release_wxverifycodereqinfo();


	//deviceQuest.release_baserequest();
	//deviceQuest.release_basereqinfo();


	return req;

}


std::string PB_NewInit(void*Au,string Aes)
{

	string req;
	WxUser*Auth = (WxUser*)Au;
	
	FromCs::NewInitRequest newinitReq;

	string data = Hex2bin("0A440A1049AA7DB2F4A3FFE0E96218F6B92CDE3210959AEF3A1A1049AA7DB2F4A3FFE0E96218F6B92CDE3220A4829CB0012A1169506164206950686F6E65204F53382E34300312086A647931313031321A04080012002204080012002A057A685F434E");

	newinitReq.ParseFromArray(data.c_str(), data.size());

	FromCs::BaseRequest*pInfo = new FromCs::BaseRequest;


	pInfo->set_sessionkey(Aes);
	pInfo->set_uin(Auth->m_uin);

	
	pInfo->set_deviceid(Auth->s_deviceID);
	pInfo->set_clientversion(0x16070124);
	pInfo->set_devicetype("iPad iPhone OS8.4");
	pInfo->set_scene(3);
	//pTag3->set_buffer(string(""));
	///pTag3->set_ilen(0);
	//pTag4->set_buffer(string(""));
	//pTag4->set_ilen(0);

	newinitReq.set_allocated_base(pInfo);
	newinitReq.set_username(Auth->m_UserName.c_str());
	//newinitReq.set_allocated_sync_key_cur(pTag3);
	//newinitReq.set_allocated_sync_key_max(pTag4);
	//newinitReq.set_language("zh_CN");

	newinitReq.SerializeToString(&req);
	string json;
	pbjson::pb2json(&newinitReq, json);
	cout << json.c_str() << "\n" << endl;
	newinitReq.release_base();

	delete pInfo;

	return req;

	

}
std::string PB_NewSync(std::string&strSyncKey)
{	
	string req;
	
	com::tencent::mars::microchat::proto::NewSyncRequest newsyncReq;
	com::tencent::mars::microchat::proto::NewSyncRequest::continueFlag_ *pFlag = new com::tencent::mars::microchat::proto::NewSyncRequest::continueFlag_;
	com::tencent::mars::microchat::proto::syncMsgKey_ *pSyncMsgKey = new com::tencent::mars::microchat::proto::syncMsgKey_;
	com::tencent::mars::microchat::proto::syncMsgKey_::MsgKey_ *pMsgKey = new com::tencent::mars::microchat::proto::syncMsgKey_::MsgKey_;

	
	//本地同步key丢失时,使用全0的KV初始化同步消息
	if (!strSyncKey.size())
	{
		//共27种消息需要同步
		const int nMsgTypeCnt = 27;
		const int nMsgType[] = { 1,2,3,4,5,7,8,9,10,11,13,14,
			101,102,103,104,105,107,109,111,112,
			201,203,204,205,1000,1001 };
		pMsgKey->set_size(nMsgTypeCnt);
		for (int i = 0; i < nMsgTypeCnt; i++)
		{
			com::tencent::mars::microchat::proto::syncMsgKey_::MsgKey_::Key_ *pKey = pMsgKey->add_key();;
			pKey->set_type(nMsgType[i]);
			pKey->set_synckey(0);
		}

		pSyncMsgKey->set_len(pMsgKey->ByteSize());
		pSyncMsgKey->set_allocated_msgkey(pMsgKey);

		strSyncKey = pSyncMsgKey->SerializePartialAsString();
	}
	


	pFlag->set_flag(0);
	newsyncReq.set_allocated_continueflag(pFlag);
	newsyncReq.set_selector(262151);		//固定值
	newsyncReq.set_tagmsgkey(strSyncKey);
	newsyncReq.set_scene(3);
	newsyncReq.set_device("iPad iPhone OS8.4");
	newsyncReq.set_syncmsgdigest(1);

	newsyncReq.SerializeToString(&req);

	
	

	//com::tencent::mars::microchat::proto::syncMsgKey_ *pSyncMsgKey = new com::tencent::mars::microchat::proto::syncMsgKey_;
	//com::tencent::mars::microchat::proto::syncMsgKey_::MsgKey_ *pMsgKey = new com::tencent::mars::microchat::proto::syncMsgKey_::MsgKey_;


	//本地同步key丢失时,使用全0的KV初始化同步消息
	


	return req;
}

////std::string PB_GetA8Key(void*handle,const char*username)
////{
////	WxUser*Auth = (WxUser*)handle;
////	micromsg::GetA8KeyReq req;
////	micromsg::BaseRequest *base = new micromsg::BaseRequest();
////	base->set_sessionkey(Auth->m_AesKey.c_str());
////	base->set_uin(0);
////	//string guid15 = string(Auth->m_deviceid.c_str(), 15);
////	base->set_deviceid(Auth->s_deviceID.c_str());
////	base->set_clientversion(0x16070124);
////	base->set_devicetype("iPad iPhone OS8.4");
////	base->set_scene(18);
////	req.set_allocated_baserequest(base);
////	req.set_bundleid("com.tencent.xin");
////	req.set_flag(0);
////	req.set_nettype("WIFI");
////	req.set_opcode(0);
////	req.set_username(username);
////	
////
////}