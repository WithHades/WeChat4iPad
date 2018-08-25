#pragma once


#include "BlockDumpList.pb.h"
#include "mmappmsg.pb.h"
#include "mmbackup.pb.h"
#include "mmbottle.pb.h"
#include "mmbuiltintype.pb.h"
#include "mmcard.pb.h"
#include "mmcontact.pb.h"
#include "mmemotion.pb.h"
#include "mmemotionstore.pb.h"
#include "mmextsend.pb.h"
#include "mmfav.pb.h"
#include "mmgame.pb.h"
#include "mmimg.pb.h"
#include "mmlbs.pb.h"
#include "mmopenapi.pb.h"
#include "mmpay.pb.h"
#include "mmprimsend.pb.h"
#include "mmremind.pb.h"
#include "mmsns.pb.h"
#include "mmsync.pb.h"
#include "mmtalk.pb.h"
#include "mmtrack.pb.h"
#include "mmvoiceaddr.pb.h"
#include "mmvoiceprint.pb.h"
#include "mmvoip.pb.h"
#include "mmvoiphw.pb.h"
#include "mmweb.pb.h"


#include "stdafx.h"
#include "mmlogin.pb.h"
#include "mmbase.pb.h"
#include "NewInit.pb.h"
#include "newsync.pb.h"



enum CGI_TYPE {
	CGI_TYPE_INVALID = -1,
	CGI_TYPE_UNKNOWN = 0,

	CGI_TYPE_NEWSYNC = 138,
	CGI_TYPE_NEWINIT = 139,
	CGI_TYPE_GETPROFILE = 302,
	CGI_TYPE_MANUALAUTH = 701,
	CGI_TYPE_NEWSENDMSG = 522,
	CGI_TYPE_MEMBERDETAIL = 551,
	CGI_TYPE_SEARCHCONTACT = 106,
	CGI_TYPE_GETCONTACT = 182,
	CGI_TYPR_GETLOGINQRCODE = 502,
	CGI_TYPR_CHECKQRCODE = 503,
	CGI_TYPE_VERIFYUSER = 30,
	CGI_TYPE_BIND = 145,
	CGI_TYPE_AUTH = 101,
	CGI_TYPE_SENDMSG = 104,
	CGI_TYPE_SYNC = 103,
	CGI_TYPE_UPLOADMSGIMG = 110,
	CGI_TYPE_GETMSGIMG = 109,
	CGI_TYPE_INIT = 121,
	CGI_TYPE_GETUPDATEPACK = 114,
	CGI_TYPE_SEARCHFRIEND = 124,
	CGI_TYPE_GETINVITEFRIEND = 115,
	CGI_TYPE_UPLOADVOICE = 127,
	CGI_TYPE_DOWNLOADVOICE = 128,


	CGI_TYPE_NEWREG = 126,
	CGI_TYPE_GETUSERNAME = 125,
	CGI_TYPE_BATCHGETCONTACTPROFILE = 140,
	CGI_TYPE_BATCHGETHEADIMG = 123,
	CGI_TYPE_GETUPDATEINFO = 113,
	CGI_TYPE_ADDCHATROOMMEMBER = 120,
	CGI_TYPE_CREATECHATROOM = 119,
	CGI_TYPE_GETVERIFYIMG = 107,
	CGI_TYPE_GETQQGROUP = 143,

	CGI_TYPE_OPLOG = 681,
	CGI_TYPE_FACEGROUP = 653,
	CGI_TYPE_SENDCARD = 131,
	CGI_TYPE_SENDINVITEMAIL = 116,
	CGI_TYPE_UPLOADMCONTACT = 133,
	CGI_TYPE_BINDOPMOBILEFORREG = 145,
	CGI_TYPE_LBSFIND = 148,
	CGI_TYPE_BINDOPMOBILE = 132,
	CGI_TYPE_GENERALSET = 177,
	CGI_TYPE_REPORTSTRATEGY = 308,
	CGI_TYPE_KVREPORT = 310,
	CGI_TYPE_STATREPORT = 250,
	CGI_TYPE_REPORTKVCOMM = 430,
	CGI_TYPE_NEWREPORTKVCOMM = 996,
	CGI_TYPE_REPORTKVCOMMRSA = 499,
	CGI_TYPE_NEWREPORTKVCOMMRSA = 997,
	CGI_TYPE_GETKVIDKEYSTRATEGY = 988,
	CGI_TYPE_GETKVIDKEYSTRATEGYRSA = 989,
	CGI_TYPE_GETLOGINQRCODE = 502,
	CGI_TYPE_CHECKLOGINQRCODE = 503,
	CGI_TYPE_STATUSNOTIFY = 251,
	CGI_TYPE_UPLOADAPPATTACH = 220,
	CGI_TYPE_DOWNLOADAPPATTACH = 221,
	CGI_TYPE_SENDAPPMSG = 222,
	CGI_TYPE_GETAPPINFO = 231,
	CGI_TYPE_DELCHATROOMMEMBER = 179,
	CGI_TYPE_GETCDNDNS = 379,
	CGI_TYPE_SENDFEEDBACK = 153,
	CGI_TYPE_SENDEMOJI = 175,
	CGI_TYPE_RECEIVEEMOJI = 176,
	CGI_TYPE_UPLOADVIDEO = 149,
	CGI_TYPE_DOWNLOADVIDEO = 150,
	CGI_TYPE_HEARTBEAT = 518,
	CGI_TYPE_BAKCHATCREATEQRCODE = 704,
	CGI_TYPE_INVITECHATROOMMEMBER = 610,
	CGI_TYPE_REVOKEMSG = 594,
	CGI_TYPE_FAVSYNC = 400,
	CGI_TYPE_BATCHGETFAVITEM = 402,
	CGI_TYPE_GETFAVINFO = 438,
	CGI_TYPE_ADDFAVITEM = 401,
	CGI_TYPE_CHECKCDN = 404,
	CGI_TYPE_MODFAVITEM = 426,
	CGI_TYPE_BATCHDELFAVITEM = 403,
	CGI_TYPE_GETLOCIMG = 648,
	CGI_TYPE_GETEMOTIONLIST = 411,
	CGI_TYPE_GETCHATROOMMEMBERDETAIL = 551,
	CGI_TYPE_MMBATCHEMOJIDOWNLOAD = 697,
	CGI_TYPE_MMBACKUPEMOJIOPERATE = 698,
	CGI_TYPE_MMEMOJIUPLOAD = 703,
	CGI_TYPE_SENDSIGHT = 245,
	CGI_TYPE_CLICKCOMMAND = 359,
	CGI_TYPE_CHECKVOICETRANS = 546,
	CGI_TYPE_UPLOADVOICEFORTRANS = 547,
	CGI_TYPE_GETVOICETRANSRES = 548,
	CGI_TYPE_TENPAY = 385,
	CGI_TYPE_REPORTIDKEY = 693,
	CGI_TYPE_REPORTIDKEYRSA = 694,
	CGI_TYPE_NEWREPORTIDKEY = 986,
	CGI_TYPE_NEWREPORTIDKEYRSA = 987,
	CGI_TYPE_GETEMOTIONDETAIL = 412,
	CGI_TYPE_MODEMOTIONPACK = 413,
	CGI_TYPE_GETEMOTIONDESC = 521,
	CGI_TYPE_EXTDEVICEINIT = 977,
	CGI_TYPE_CHECKBIGFILEUPLOAD = 727,
	CGI_TYPE_CHECKBIGFILEDOWNLOAD = 728,
	CGI_TYPE_CREATETALKROOM = 1918,
	CGI_TYPE_ENTERTALKROOM = 1919,
	CGI_TYPE_VOICEACKREQ = 1935,
	CGI_TYPE_EXITTALKROOM = 1927,
	CGI_TYPE_CANCELCREATETALKROOM = 1928,
	CGI_TYPE_REJECTENTERTALKROOM = 1929,
	CGI_TYPE_ADDMEMBERS = 1931,
	CGI_TYPE_HELLOTALKROOM = 1932,
	CGI_TYPE_MISCINFO = 1933,
	CGI_TYPE_MODIFYGROUPINFO = 1934,
	CGI_TYPE_CLIENTSCENEREPORT = 1936,
	CGI_TYPE_VOICEREDIRECTREQ = 1937,
	CGI_TYPE_GETGROUPINFOBATCH = 1938,
	CGI_TYPE_MEMBERWHISPER = 1939,
	CGI_TYPE_PSTNINVITE = 991,
	CGI_TYPE_PSTNSYNC = 819,
	CGI_TYPE_PSTNCANCELINVITE = 843,
	CGI_TYPE_PSTNSHUTDOWN = 723,
	CGI_TYPE_PSTNHEARTBEAT = 824,
	CGI_TYPE_GETWECHATOUTCOUPONS = 257,
	CGI_TYPE_JSAPIPREVERIFY = 1093,
	CGI_TYPE_JSAPIAUTH = 1095,
	CGI_TYPE_JSAPIREALTIMEVERIFY = 1094,
	CGI_TYPE_JSAPISETAUTH = 1096,
	CGI_TYPE_PSTNREDIRECT = 726,
	CGI_TYPE_CONVERTBIZCHAT = 1315,
	CGI_TYPE_GETBIZJSAPIREDIRECTURL = 1393,
	CGI_TYPE_GETCRMSG = 805,
	CGI_TYPE_USRMSGMMBIZJSAPIUPLOADCDNINFO = 1034,
	CGI_TYPE_USRMSGMMBIZJSAPIDOWNLOADCDNINFO = 1035,
	CGI_TYPE_BIZATTRBIZATTRSYNC = 1075,
	CGI_TYPE_GETTRANSTEXT = 631,
	CGI_TYPE_GETCHATROOMINFODETAIL = 223,
	CGI_TYPE_SETCHATROOMANNOUNCEMENT = 993,
	CGI_TYPE_CHECKMD5 = 939,
	CGI_TYPE_GETABTEST = 1801,
	CGI_TYPE_BINDQUERYNEW = 1501,

	CGI_TYPE_AUTOAUTH = 702,

	CGI_TYPE_MMWEBSEARCH = 719,
	CGI_TYPE_SEARCHSUGGESTION = 1161,
	CGI_TYPE_GETBIZCHATINFO = 1352,

	CGI_TYPE_GETBIZCHATUSERDETAILLIST = 1390,
	CGI_TYPE_CREATEBIZCHATINFO = 1355,
	CGI_TYPE_GETBIZCHATINFOLIST = 1365,
	CGI_TYPE_GETBIZCHATMYUSERINFO = 1354,
	CGI_TYPE_GETBIZCHATUSERINFOLIST = 1353,
	CGI_TYPE_GETFAVBIZCHATLIST = 1367,
	CGI_TYPE_INITIATEBIZCHAT = 1389,
	CGI_TYPE_QUITBIZCHAT = 1358,
	CGI_TYPE_QYMSGSTATENOTIFY = 1361,
	CGI_TYPE_SETBRANDFLAG = 1363,
	CGI_TYPE_UPDATEBIZCHAT = 1356,
	CGI_TYPE_UPDATEBIZCHATMEMBERLIST = 1357,
	CGI_TYPE_REPORTCLIENTCHECK = 771,
	CGI_TYPE_INITCONTACT = 851,
	CGI_TYPE_BATCHGETCONTACTBRIEFINFO = 945,
	CGI_TYPE_PUSH = 10001,

	CGI_TYPE_MAX = 0xFFFF
};


#define CGI_NEWSYNC						"/cgi-bin/micromsg-bin/newsync"					//同步服务端最新消息
#define CGI_MANUALAUTH					"/cgi-bin/micromsg-bin/manualauth"				//登录
#define CGI_NEWSENDMSG					"/cgi-bin/micromsg-bin/newsendmsg"				//发送文字消息
#define CGI_NEWINIT						"/cgi-bin/micromsg-bin/newinit"					//首次登录,初始化数据库
#define	CGI_GETPROFILE					"/cgi-bin/micromsg-bin/getprofile"				//获取个人信息
#define	CGI_SEARCHCONTACT				"/cgi-bin/micromsg-bin/searchcontact"			//搜索新朋友
#define	CGI_GETCONTACT					"/cgi-bin/micromsg-bin/getcontact"				//查找新朋友
#define	CGI_VERIFYUSER					"/cgi-bin/micromsg-bin/verifyuser"				//添加好友
#define CGI_BIND						"/cgi-bin/micromsg-bin/bindopmobileforreg"		//首次登录短信授权
#define CGI_QRCODE						"/cgi-bin/micromsg-bin/getloginqrcode"
#define CGI_MEMBERDETAIL				"/cgi-bin/micromsg-bin/getchatroommemberdetail"


#define CGI_OPTION						 "/cgi-bin/micromsg-bin/oplog"
#define CGI_AUTH						 "/cgi-bin/micromsg-bin/auth"
#define CGI_SENDMSG					    "/cgi-bin/micromsg-bin/sendmsg"
#define CGI_SYNC					     "/cgi-bin/micromsg-bin/sync"
#define CGI_UPLOADMSGIMG			      "/cgi-bin/micromsg-bin/uploadmsgimg"
#define CGI_GETMSGIMG					  "/cgi-bin/micromsg-bin/getmsgimg"
#define CGI_INIT						 "/cgi-bin/micromsg-bin/init"
#define CGI_GETUPDATEPACK					   "/cgi-bin/micromsg-bin/getupdatepack"
#define CGI_SEARCHFRIEND				  "/cgi-bin/micromsg-bin/searchfriend"
#define CGI_GETINVITEFRIEND        "/cgi-bin/micromsg-bin/getinvitefriend"
#define CGI_UPLOADVOICE        "/cgi-bin/micromsg-bin/uploadvoice"
#define CGI_DOWNLOADVOICE        "/cgi-bin/micromsg-bin/downloadvoice"
#define CGI_NEWINIT        "/cgi-bin/micromsg-bin/newinit"
#define CGI_NEWSYNC        "/cgi-bin/micromsg-bin/newsync"
#define CGI_NEWREG        "/cgi-bin/micromsg-bin/newreg"
#define CGI_GETUSERNAME        "/cgi-bin/micromsg-bin/getusername"
#define CGI_BATCHGETCONTACTPROFILE        "/cgi-bin/micromsg-bin/batchgetcontactprofile"
#define CGI_BATCHGETHEADIMG        "/cgi-bin/micromsg-bin/batchgetheadimg"
#define CGI_GETUPDATEINFO        "/cgi-bin/micromsg-bin/getupdateinfo"
#define CGI_ADDCHATROOMMEMBER        "/cgi-bin/micromsg-bin/addchatroommember"
#define CGI_CREATECHATROOM        "/cgi-bin/micromsg-bin/createchatroom"
#define CGI_FACECREATGROUP        "/cgi-bin/micromsg-bin/mmfacingcreatechatroom"
#define CGI_GETVERIFYIMG        "/cgi-bin/micromsg-bin/getverifyimg"
#define CGI_GETQQGROUP        "/cgi-bin/micromsg-bin/getqqgroup"
#define CGI_VERIFYUSER        "/cgi-bin/micromsg-bin/verifyuser"
#define CGI_SEARCHCONTACT        "/cgi-bin/micromsg-bin/searchcontact"
#define CGI_SENDCARD        "/cgi-bin/micromsg-bin/sendcard"
#define CGI_SENDINVITEMAIL        "/cgi-bin/micromsg-bin/sendinvitemail"
#define CGI_UPLOADMCONTACT        "/cgi-bin/micromsg-bin/uploadmcontact"
#define CGI_BINDOPMOBILEFORREG        "/cgi-bin/micromsg-bin/bindopmobileforreg"
#define CGI_LBSFIND        "/cgi-bin/micromsg-bin/lbsfind"
#define CGI_BINDOPMOBILE        "/cgi-bin/micromsg-bin/bindopmobile"
#define CGI_GENERALSET        "/cgi-bin/micromsg-bin/generalset"
#define CGI_REPORTSTRATEGY        "/cgi-bin/micromsg-bin/reportstrategy"
#define CGI_KVREPORT        "/cgi-bin/micromsg-bin/kvreport"
#define CGI_STATREPORT        "/cgi-bin/micromsg-bin/statreport"
#define CGI_REPORTKVCOMM        "/cgi-bin/micromsg-bin/reportkvcomm"
#define CGI_NEWREPORTKVCOMM        "/cgi-bin/micromsg-bin/newreportkvcomm"
#define CGI_REPORTKVCOMMRSA        "/cgi-bin/micromsg-bin/reportkvcommrsa"
#define CGI_NEWREPORTKVCOMMRSA        "/cgi-bin/micromsg-bin/newreportkvcommrsa"
#define CGI_GETKVIDKEYSTRATEGY        "/cgi-bin/micromsg-bin/getkvidkeystrategy"
#define CGI_GETKVIDKEYSTRATEGYRSA        "/cgi-bin/micromsg-bin/getkvidkeystrategyrsa"
#define CGI_GETLOGINQRCODE        "/cgi-bin/micromsg-bin/getloginqrcode"
#define CGI_CHECKLOGINQRCODE        "/cgi-bin/micromsg-bin/checkloginqrcode"
#define CGI_STATUSNOTIFY        "/cgi-bin/micromsg-bin/statusnotify"
#define CGI_UPLOADAPPATTACH        "/cgi-bin/micromsg-bin/uploadappattach"
#define CGI_DOWNLOADAPPATTACH        "/cgi-bin/micromsg-bin/downloadappattach"
#define CGI_SENDAPPMSG        "/cgi-bin/micromsg-bin/sendappmsg"
#define CGI_GETAPPINFO        "/cgi-bin/micromsg-bin/getappinfo"
#define CGI_DELCHATROOMMEMBER        "/cgi-bin/micromsg-bin/delchatroommember"
#define CGI_GETCDNDNS        "/cgi-bin/micromsg-bin/getcdndns"
#define CGI_SENDFEEDBACK        "/cgi-bin/micromsg-bin/sendfeedback"
#define CGI_SENDEMOJI        "/cgi-bin/micromsg-bin/sendemoji"
#define CGI_RECEIVEEMOJI        "/cgi-bin/micromsg-bin/receiveemoji"
#define CGI_UPLOADVIDEO        "/cgi-bin/micromsg-bin/uploadvideo"
#define CGI_DOWNLOADVIDEO        "/cgi-bin/micromsg-bin/downloadvideo"
#define CGI_HEARTBEAT        "/cgi-bin/micromsg-bin/heartbeat"
#define CGI_BAKCHATCREATEQRCODE        "/cgi-bin/micromsg-bin/bakchatcreateqrcode"
#define CGI_INVITECHATROOMMEMBER        "/cgi-bin/micromsg-bin/invitechatroommember"
#define CGI_REVOKEMSG        "/cgi-bin/micromsg-bin/revokemsg"
#define CGI_FAVSYNC        "/cgi-bin/micromsg-bin/favsync"
#define CGI_BATCHGETFAVITEM        "/cgi-bin/micromsg-bin/batchgetfavitem"
#define CGI_GETFAVINFO        "/cgi-bin/micromsg-bin/getfavinfo"
#define CGI_ADDFAVITEM        "/cgi-bin/micromsg-bin/addfavitem"
#define CGI_CHECKCDN        "/cgi-bin/micromsg-bin/checkcdn"
#define CGI_MODFAVITEM        "/cgi-bin/micromsg-bin/modfavitem"
#define CGI_BATCHDELFAVITEM        "/cgi-bin/micromsg-bin/batchdelfavitem"
#define CGI_GETLOCIMG        "/cgi-bin/micromsg-bin/getlocimg"
#define CGI_GETEMOTIONLIST        "/cgi-bin/micromsg-bin/getemotionlist"
#define CGI_GETCHATROOMMEMBERDETAIL        "/cgi-bin/micromsg-bin/getchatroommemberdetail"
#define CGI_MMBATCHEMOJIDOWNLOAD        "/cgi-bin/micromsg-bin/mmbatchemojidownload"
#define CGI_MMBACKUPEMOJIOPERATE        "/cgi-bin/micromsg-bin/mmbackupemojioperate"
#define CGI_MMEMOJIUPLOAD        "/cgi-bin/micromsg-bin/mmemojiupload"
#define CGI_SENDSIGHT        "/cgi-bin/micromsg-bin/sendsight"
#define CGI_CLICKCOMMAND        "/cgi-bin/micromsg-bin/clickcommand"
#define CGI_CHECKVOICETRANS        "/cgi-bin/micromsg-bin/checkvoicetrans"
#define CGI_UPLOADVOICEFORTRANS        "/cgi-bin/micromsg-bin/uploadvoicefortrans"
#define CGI_GETVOICETRANSRES        "/cgi-bin/micromsg-bin/getvoicetransres"
#define CGI_TENPAY        "/cgi-bin/micromsg-bin/tenpay"
#define CGI_REPORTIDKEY        "/cgi-bin/micromsg-bin/reportidkey"
#define CGI_REPORTIDKEYRSA        "/cgi-bin/micromsg-bin/reportidkeyrsa"
#define CGI_NEWREPORTIDKEY        "/cgi-bin/micromsg-bin/newreportidkey"
#define CGI_NEWREPORTIDKEYRSA        "/cgi-bin/micromsg-bin/newreportidkeyrsa"
#define CGI_GETEMOTIONDETAIL        "/cgi-bin/micromsg-bin/getemotiondetail"
#define CGI_MODEMOTIONPACK        "/cgi-bin/micromsg-bin/modemotionpack"
#define CGI_GETEMOTIONDESC        "/cgi-bin/micromsg-bin/getemotiondesc"
#define CGI_EXTDEVICEINIT        "/cgi-bin/micromsg-bin/extdeviceinit"
#define CGI_CHECKBIGFILEUPLOAD        "/cgi-bin/micromsg-bin/checkbigfileupload"
#define CGI_CHECKBIGFILEDOWNLOAD        "/cgi-bin/micromsg-bin/checkbigfiledownload"
#define CGI_CREATETALKROOM        "/cgi-bin/qcwxmultitalk-bin/createtalkroom"
#define CGI_ENTERTALKROOM        "/cgi-bin/qcwxmultitalk-bin/entertalkroom"
#define CGI_VOICEACKREQ        "/cgi-bin/qcwxmultitalk-bin/voiceackreq"
#define CGI_EXITTALKROOM        "/cgi-bin/qcwxmultitalk-bin/exittalkroom"
#define CGI_CANCELCREATETALKROOM        "/cgi-bin/qcwxmultitalk-bin/cancelcreatetalkroom"
#define CGI_REJECTENTERTALKROOM        "/cgi-bin/qcwxmultitalk-bin/rejectentertalkroom"
#define CGI_ADDMEMBERS        "/cgi-bin/qcwxmultitalk-bin/addmembers"
#define CGI_HELLOTALKROOM        "/cgi-bin/qcwxmultitalk-bin/hellotalkroom"
#define CGI_MISCINFO        "/cgi-bin/qcwxmultitalk-bin/miscinfo"
#define CGI_MODIFYGROUPINFO        "/cgi-bin/qcwxmultitalk-bin/modifygroupinfo"
#define CGI_CLIENTSCENEREPORT        "/cgi-bin/qcwxmultitalk-bin/clientscenereport"
#define CGI_VOICEREDIRECTREQ        "/cgi-bin/qcwxmultitalk-bin/voiceredirectreq"
#define CGI_GETGROUPINFOBATCH        "/cgi-bin/qcwxmultitalk-bin/getgroupinfobatch"
#define CGI_MEMBERWHISPER        "/cgi-bin/qcwxmultitalk-bin/memberwhisper"
#define CGI_PSTNINVITE        "/cgi-bin/micromsg-bin/pstninvite"
#define CGI_PSTNSYNC        "/cgi-bin/micromsg-bin/pstnsync"
#define CGI_PSTNCANCELINVITE        "/cgi-bin/micromsg-bin/pstncancelinvite"
#define CGI_PSTNSHUTDOWN        "/cgi-bin/micromsg-bin/pstnshutdown"
#define CGI_PSTNHEARTBEAT        "/cgi-bin/micromsg-bin/pstnheartbeat"
#define CGI_GETWECHATOUTCOUPONS        "/cgi-bin/micromsg-bin/getwechatoutcoupons"
#define CGI_JSAPIPREVERIFY        "/cgi-bin/mmbiz-bin/jsapi-preverify"
#define CGI_JSAPIAUTH        "/cgi-bin/mmbiz-bin/jsapi-auth"
#define CGI_JSAPIREALTIMEVERIFY        "/cgi-bin/mmbiz-bin/jsapi-realtimeverify"
#define CGI_JSAPISETAUTH        "/cgi-bin/mmbiz-bin/jsapi-setauth"
#define CGI_PSTNREDIRECT        "/cgi-bin/micromsg-bin/pstnredirect"
#define CGI_CONVERTBIZCHAT        "/cgi-bin/mmocbiz-bin/convertbizchat"
#define CGI_GETBIZJSAPIREDIRECTURL        "/cgi-bin/mmocbiz-bin/getbizjsapiredirecturl"
#define CGI_GETCRMSG        "/cgi-bin/micromsg-bin/getcrmsg"
#define CGI_MMBIZJSAPI_UPLOADCDNINFO        "/cgi-bin/mmbiz-bin/usrmsg/mmbizjsapi_uploadcdninfo"
#define CGI_MMBIZJSAPI_DOWNLOADCDNINFO        "/cgi-bin/mmbiz-bin/usrmsg/mmbizjsapi_downloadcdninfo"
#define CGI_BIZATTRSYNC        "/cgi-bin/mmbiz-bin/bizattr/bizattrsync"
#define CGI_GETTRANSTEXT        "/cgi-bin/micromsg-bin/gettranstext"
#define CGI_GETCHATROOMINFODETAIL        "/cgi-bin/micromsg-bin/getchatroominfodetail"
#define CGI_SETCHATROOMANNOUNCEMENT        "/cgi-bin/micromsg-bin/setchatroomannouncement"
#define CGI_CHECKMD5        "/cgi-bin/micromsg-bin/checkmd5"
#define CGI_GETABTEST        "/cgi-bin/mmux-bin/getabtest"
#define CGI_BINDQUERYNEW        "/cgi-bin/mmpay-bin/tenpay/bindquerynew"
#define CGI_MANUALAUTH        "/cgi-bin/micromsg-bin/manualauth"
#define CGI_AUTOAUTH        "/cgi-bin/micromsg-bin/autoauth"
#define CGI_GETFAVINFO        "/cgi-bin/micromsg-bin/getfavinfo"
#define CGI_MMWEBSEARCH        "/cgi-bin/micromsg-bin/mmwebsearch"
#define CGI_SEARCHSUGGESTION        "/cgi-bin/mmsearch-bin/searchsuggestion"
#define CGI_GETBIZCHATINFO        "/cgi-bin/mmocbiz-bin/getbizchatinfo"
#define CGI_GETBIZCHATINFO        "/cgi-bin/mmocbiz-bin/getbizchatinfo"
#define CGI_GETBIZCHATUSERDETAILLIST        "/cgi-bin/mmocbiz-bin/getbizchatuserdetaillist"
#define CGI_CREATEBIZCHATINFO        "/cgi-bin/mmocbiz-bin/createbizchatinfo"
#define CGI_GETBIZCHATINFOLIST        "/cgi-bin/mmocbiz-bin/getbizchatinfolist"
#define CGI_GETBIZCHATMYUSERINFO        "/cgi-bin/mmocbiz-bin/getbizchatmyuserinfo"
#define CGI_GETBIZCHATUSERINFOLIST        "/cgi-bin/mmocbiz-bin/getbizchatuserinfolist"
#define CGI_GETFAVBIZCHATLIST        "/cgi-bin/mmocbiz-bin/getfavbizchatlist"
#define CGI_INITIATEBIZCHAT        "/cgi-bin/mmocbiz-bin/initiatebizchat"
#define CGI_QUITBIZCHAT        "/cgi-bin/mmocbiz-bin/quitbizchat"
#define CGI_QYMSGSTATENOTIFY        "/cgi-bin/mmocbiz-bin/qymsgstatenotify"
#define CGI_SETBRANDFLAG        "/cgi-bin/mmocbiz-bin/setbrandflag"
#define CGI_UPDATEBIZCHAT        "/cgi-bin/mmocbiz-bin/updatebizchat"
#define CGI_UPDATEBIZCHATMEMBERLIST        "/cgi-bin/mmocbiz-bin/updatebizchatmemberlist"
#define CGI_REPORTCLIENTCHECK        "/cgi-bin/micromsg-bin/reportclientcheck"
#define CGI_INITCONTACT        "/cgi-bin/micromsg-bin/initcontact"
#define CGI_BATCHGETCONTACTBRIEFINFO        "/cgi-bin/micromsg-bin/batchgetcontactbriefinfo"
