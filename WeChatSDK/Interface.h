#pragma once
#include "stdafx.h"
#include "WxUser.h"
#include "curl/curl.h"





/*                             */
#define JS_API _stdcall

void* WINAPI WxInitHandle(const char*IMEI, const char*deviceNAME, const char*deviceUUID, const char*deviceTYPE);


typedef void(*QRCODECallBack)(void*result,int CGI);
static void * JS_API js_defaultalloc(void *actx, void *ptr, int size);
void WINAPI WXUserLogin(void*handle, const char*username, const char*password, char**pushStr);
void WINAPI SaveInfo(const char*username, void* src);

string GenAesKey();
void WINAPI SafeFree(void *p);
void WINAPI WXQRCodeLogin(void*handle);
void WINAPI WxGetQRCode(void*handle);
void WINAPI WxCheckQRCode(void*handle);
void WINAPI WxNewInit(void*handle);
void WINAPI WxSyncMsg(void*handle, char**pushStr);

QRCODECallBack _qrcodeback = NULL;
void WINAPI SetQRCodeCallBack(QRCODECallBack callback);
void WINAPI QRCodeCallBack(void*src,int);
/*                             */
void WINAPI postLocal(std::string postParams);
CURLcode curl_post_req(const string &url, const string &postParams, string &response);
void WINAPI testCheck();
std::string mm_post(std::string url_post, std::string postParams);

size_t req_reply(void *ptr, size_t size, size_t nmemb, void *stream);